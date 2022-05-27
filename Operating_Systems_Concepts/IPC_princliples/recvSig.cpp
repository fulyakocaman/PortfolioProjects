#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include "msg.h"    /* For the macros */

using namespace std;

/* The size of the shared memory segment */
#define SHARED_MEMORY_CHUNK_SIZE 1000

/* The id for the shared memory segment */
int shmid;

/* The pointer to the shared memory */
void *sharedMemPtr = NULL;

/* The process id for the sender */
pid_t pidSender;

/* The file name received from the sender */
string fileName;

/* The size of the message received from the sender */
int msgSize = -1;

/* The number of bytes received */
int numBytesRecv = 0;

/* The receiver gets the signal from the sender and reads pidSender */
void pid_init_handler(int arg) {
  /* Reads the sender's pid from the shared memory and stores it to pidSender*/
  pidSender = ((int *)sharedMemPtr)[0];

}

/* The receiver gets the signal from the sender and reads the fileName */
void fileName_handler(int arg) {

  char name[MAX_FILE_NAME_SIZE];

  /* Reads the fileName and stores it to name */
  strncpy(name, (char *)sharedMemPtr, MAX_FILE_NAME_SIZE);

  /* Returns the received file name */
  fileName = name;

}

/* The receiver gets the signal from the sender and reads the file size */
void size_handler(int arg) {
  /* Reads size from the sender and stores it to msgSize */
  msgSize = ((int*)sharedMemPtr)[0];

}

/**
 * The function for receiving the name of the file
 * @return - the name of the file received from the sender
 */
string recvFileName()
{
	/* Initialize the handler to fileName initialization */
	if (signal(SIGUSR1, fileName_handler) == SIG_ERR)
	{
		perror("signal");
		exit(-1);
	}


  return fileName;
}

 /**
 * Sets up the shared memory segment and message queue
 * @param shmid - the id of the allocated shared memory
 * @param sharedMemPtr - the pointer to the shared memory
 */
void init(int& shmid, void*& sharedMemPtr)
{
	/* Initialize the handler to pid initialization */
	if (signal(SIGUSR1, pid_init_handler) == SIG_ERR)
	{
		perror("signal");
		exit(-1);
	}

	/* Use ftok to generate the key. */
	key_t key = ftok("keyfile.txt", 'b');

	/* Make sure the key generation succeeded */
	if(key < 0)
	{
		perror("ftok");
		exit(-1);
	}

	/* Allocate a shared memory segment */
	shmid = shmget(key, SHARED_MEMORY_CHUNK_SIZE, IPC_CREAT | 0666);

	/* Failed to allocate shared memory */
  if(shmid < 0)
  {
  	perror("shmget");
 	  exit(-1);
  }

	/* Attach to the shared memory */
  sharedMemPtr = shmat (shmid, 0, 0);

	/*  Error checks */
	if(sharedMemPtr < 0)
	{
		perror("shmat");
		exit(-1);
	}

	/* Writes receiver's pid into the shared memory */
	((int *)sharedMemPtr)[0] = getpid();

	 while(1); //sleep

	/* Store the ID and the pointer to the shared memory region in the
	corresponding parameters */
	shmid = shmid;
	sharedMemPtr = sharedMemPtr;
}


/**
 * The main loop
 * @param fileName - the name of the file received from the sender.
 * @return - the number of bytes received
 */
unsigned long mainLoop(const char* fileName)
{
	/* The string representing the file name received from the sender */
	string recvFileNameStr = fileName;

	/* Append __recv to the end of file name */
	recvFileNameStr += "_recv";

	/* Open the file for writing */
	FILE* fp = fopen(recvFileNameStr.c_str(), "w");

	/* Error checks */
	if(!fp)
	{
		perror("fopen");
		exit(-1);
	}

	/* Keep receiving until the sender sets the size to 0, indicating that
 	 * there is no more data to send.
 	 */
	while(msgSize != 0)
	{
		 /* Initialize the handler to size initialization */
		 if (signal(SIGUSR1, size_handler) == SIG_ERR)
		 {
			 perror("signal");
			 exit(-1);
		 }

		 msgSize = numBytesRecv;

		/* If the sender is not telling us that we are done, then get to work */
		if(msgSize != 0)
		{
			/* Record the number of bytes received */
			/* Save into the file the data in shared memory (that was put there
			 *  by the sender)
     */
			numBytesRecv = fwrite(sharedMemPtr, 1, msgSize, fp);

			/* Signal the sender, telling ready for the next set of bytes */
      if (kill(pidSender, SIGUSR1) == -1)
			{
        perror("kill");
        exit(-1);
      }

		}
		/* We are done */
		else
		{
			/* Close the file */
			fclose(fp);
		}
	}

	return numBytesRecv;
}



/**
 * Performs cleanup functions
 * @param sharedMemPtr - the pointer to the shared memory
 * @param shmid - the id of the shared memory segment
 */
void cleanUp(const int& shmid, void* sharedMemPtr)
{
	/* Detach from shared memory */
	shmdt(sharedMemPtr);

	/* Deallocate the shared memory segment */
	if(shmctl (shmid, IPC_RMID, 0) < 0)
	{
		perror("shmctl");
	}

}

/**
 * Handles the exit signal
 * @param signal - the signal type
 */
void ctrlCSignal(int signal)
{
	/* Free system V resources */
	cleanUp(shmid, sharedMemPtr);
}

/**
 * This function handles the signal
 * @param arg - the signal number
 */
void signalHandlerFunc(int arg)
{
	ctrlCSignal(arg);
}

int main(int argc, char** argv)
{
	 /* Overide the default signal handler for the
 	 * SIGINT signal with signalHandlerFunc
 	 */
	if (signal(SIGINT, signalHandlerFunc) == SIG_ERR)
	{
			 printf("SIGINT install error\n");
			 exit(1);
	}

	/* Initialize */
	init(shmid, sharedMemPtr);

	/* Receive the file name from the sender */
	string fileName = recvFileName();

	/* Go to the main loop */
	fprintf(stderr, "The number of bytes received is: %lu\n", mainLoop(fileName.c_str()));

	/* Detach from shared memory segment, and deallocate shared memory */
	 cleanUp(shmid, sharedMemPtr);

	return 0;
}
