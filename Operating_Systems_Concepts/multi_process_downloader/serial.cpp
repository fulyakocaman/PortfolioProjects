#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	string urlName;
	ifstream file("urls.txt");

	if (file)
	{
		while(getline(file, urlName))
		{
			/* The ID of the child process */
			pid_t  pid;

			/* parent forks off a child process */
			pid = fork();

			if (pid < 0)
			{ /* error occurred */
				fprintf(stderr, "Fork Failed");
				exit(-1);
			}
			else if (pid == 0)  /* child process */
			{
				/* replaces the executable image with the wget program */
				if(execlp("/usr/bin/wget", "wget", urlName.c_str(), NULL) < 0)
				{
					perror("execlp");
					exit(-1);
				}
			}
			else /* parent process */
			{
			/* parent will wait for the child to complete */
				int exitedChildPid = wait (NULL);

				// Error checks
				if(exitedChildPid < 0)
				{
					perror("wait");
					exit(-1);
				}
			}
		}
	}
	else
	{
		cout << "Could not open file!";
	}

	file.close();

	return 0;

}
