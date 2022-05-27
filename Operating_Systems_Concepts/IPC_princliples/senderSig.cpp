#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include "msg.h"    /* For the macros */

using namespace std;

/* The size of the shared memory segment */
#define SHARED_MEMORY_CHUNK_SIZE 1000

/* The id for the shared memory segment */
int shmid;

/* The pointer to the shared memory */
void* sharedMemPtr;

/* The process id for the receiver */
pid_t pidRecv;

/* The signal from the receiver that it;s done */
void recv_done_handler(int arg)
{
   signal(SIGUSR1, recv_done_handler);
}

/**
 * Sets up the shared memory segment and message queue
 * @param shmid - the id of the allocated shared memory
 * @param sharedMemPtr - the pointer to the shared memory
 */
void init(int& shmid, void*& sharedMemPtr)
{
	/* Use ftok to generate the key. */
	key_t key = ftok("keyfile.txt", 'b');

	/* Make sure the key generation succeeded */
	if(key < 0)
	{
		perror("ftok");
		exit(-1);
	}

  /* Get the id of the shared memory segment. The size of the segment must be SHARED_MEMORY_CHUNK_SIZE */
  shmid = shmget(key, SHARED_MEMORY_CHUNK_SIZE, 0666);

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

	/* Reads the receiver's pid and stores it to pidRecv*/
  pidRecv = ((int*)sharedMemPtr)[0];

  /* Write senders pid into the shared memory */
  ((int*)sharedMemPtr)[0] = getpid();

	/* Signal the receiver, telling him that pidSender is ready */
	if(kill(pidRecv, SIGUSR1) == -1)
	{
			perror("kill");
			exit(-1);
	}

	/* Store the ID and the pointer to the shared memory region
	in the corresponding function parameters */
	shmid = shmid;
	sharedMemPtr = sharedMemPtr;
}

/**
 * Performs the cleanup functions
 * @param sharedMemPtr - the pointer to the shared memory
 * @param shmid - the id of the shared memory segment
 */
void cleanUp(void* sharedMemPtr)
{
	/*  Detach from shared memory */
	shmdt(sharedMemPtr);

}

/**
 * The main send function
 * @param fileName - the name of the file
 * @return - the number of bytes sent
 */
unsigned long sendFile(const char* fileName)
{
	/* The number of bytes sent */
	unsigned long numBytesSent = 0;

	string numBytes;

	/* Open the file */
	FILE* fp =  fopen(fileName, "r");

	/* Was the file open? */
	if(!fp)
	{
		perror("fopen");
		exit(-1);
	}

	/* Read the whole file */
	while(!feof(fp))
	{
		/* Count the number of bytes sent. */
		numBytesSent = fread(sharedMemPtr, 1, SHARED_MEMORY_CHUNK_SIZE, fp);

		/* Store the data read*/
		char data[SHARED_MEMORY_CHUNK_SIZE];

		/* Copy the data read from the share memory to the variable data */
		strncpy(data, (char*) sharedMemPtr, SHARED_MEMORY_CHUNK_SIZE);

		/* Puts the byte count into the first 4 bytes of the shared memory */
		((int*)sharedMemPtr)[0] = numBytesSent;

		/* Then puts the data back into the shared memory */
		strncpy((char*) sharedMemPtr, data, SHARED_MEMORY_CHUNK_SIZE);

		/* Signal the receiver, telling the byte count is ready */
		if(kill(pidRecv, SIGUSR1) == -1)
		{
				perror("kill");
				exit(-1);
		}

		/* Reset the signal handler  */
		if(signal(SIGUSR1, recv_done_handler) == SIG_ERR)
		{
				perror("signal");
				exit(-1);
		}
	}

	/* Signal the receiver, telling it's done */
	if(kill(pidRecv, SIGUSR1) == -1)
	{
			perror("kill");
			exit(-1);
	}

	/* Close the file */
	fclose(fp);

	return numBytesSent;
}

/**
 * Used to send the name of the file to the receiver
 * @param fileName - the name of the file to send
 */
void sendFileName(const char* fileName)
{
	/* Get the length of the file name */
	int fileNameSize = strlen(fileName);

	/* Make sure the file name does not exceed the maximum buffer size in the
	 * fileNameMsg struct. If exceeds, then terminate with an error.
	 */
	 if (fileNameSize > MAX_FILE_NAME_SIZE)
 	{
 		fprintf(stderr, "Your string is too big (should be <= MAX_FILE_NAME_SIZE characters)\n");
 		exit(-1);
 	}

	/* Copy the file name into the shared memory */
	strncpy((char*) sharedMemPtr, fileName, MAX_FILE_NAME_SIZE);

	/* Signal the receiver, telling the fileName is ready */
	if(kill(pidRecv, SIGUSR1) == -1)
	{
		perror("kill");
		exit(-1);
	}
}


int main(int argc, char** argv)
{
	/* Check the command line arguments */
	if(argc < 2)
	{
		fprintf(stderr, "USAGE: %s <FILE NAME>\n", argv[0]);
		exit(-1);
	}

	/* Connect to shared memory */
	init(shmid, sharedMemPtr);

	/* Send the name of the file */
  sendFileName(argv[1]);

	/* Send the file */
	fprintf(stderr, "The number of bytes sent is %lu\n", sendFile(argv[1]));

	/* Cleanup */
	cleanUp(sharedMemPtr);

	return 0;
}
