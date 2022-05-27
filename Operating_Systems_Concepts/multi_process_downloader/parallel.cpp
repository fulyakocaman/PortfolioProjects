#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int numFiles(string filename)
{ /* function returns the number of lines meaning number of URLs in a file */
  int numLines = 0;
  string urlName;
  ifstream file(filename);

  if (file)
  {
    while (getline(file, urlName)) {
      ++numLines;
    }
  } else {
    cout << "Could not open file!";
  }

  file.close();

  return numLines;
}

int main()
{
  string urlName;
  ifstream file("urls.txt");

  /* The ID of the child process */
  pid_t pid;

  int num = numFiles("urls.txt");

  if (file)
  {
    while (getline(file, urlName))
    {
      /* parent forks off a child process */
      pid = fork();
      if (pid == 0) /* child process */
      {
        /* replaces the executable image with the wget program */
        if (execlp("/usr/bin/wget", "wget", urlName.c_str(), NULL) < 0)
        {
          perror("execlp");
          exit(-1);
        }
      }
    }

    if (pid < 0)
    { /* error occurred */
      fprintf(stderr, "Fork Failed");
      exit(-1);
    }
    else
    { /* parent process */
      for (int i = 0; i < num; ++i)
      { /* parent calls wait () n times (number of URLs) */
        int exitedChildPid = wait(NULL);

        // Error checks
        if (exitedChildPid < 0)
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
