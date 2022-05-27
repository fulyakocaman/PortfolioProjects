#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

int numWords(string filename)
{ /* function returns the number of words in a file */
  int num = 0;
  string wordRead;
  ifstream file(filename);

  if (file)
  {
    while (!file.eof())
    {
      file >> wordRead;
      ++num;
    }
  }
  else
  {
    cout << "Could not open file!";
  }

  file.close();

  return num;
}

int main(int argc, char **argv)
{ // To run the program: ./multi-search <FILE NAME> <KEY> <NUMBER OF PROCESSES>

  string fileName = argv[1];
  string key = argv[2];
  string strNumProcesses = argv[3];
  int numProcesses = stoi(strNumProcesses);

  string stringRead;
  int size = numWords(fileName);
  // create array of vectors to store the strings from the file
  vector<string> myVec;

  ifstream file(fileName);

  if (file)
  {
    pid_t pid;
    for (int i = 0; i < size - 1; ++i)
    {
      file >> stringRead;
      myVec.push_back(stringRead);
    }
    //  determine new size of the vector for the n sections
    int newSize = ((myVec.size() / numProcesses) + 1);
    // create array of vectors to store the sub-vectors
    vector<string> newVec[numProcesses];

    for (int j = 0; j < numProcesses; ++j)
    {
      // get range for next set of n elements
      auto start = next(myVec.cbegin(), j * newSize);       // included
      auto end = next(myVec.cbegin(), ((j + 1) * newSize)); // excluded

      // allocate memory for the sub-vector with the newSize
      newVec[j].resize(newSize);

      //copy elements from the input range to the sub-vector; range [first,last)
      copy(start, end, newVec[j].begin());
    }

    /* parent forks off n (numProcesses) child processes */
    for (int i = 0; i < numProcesses; i++)
    {
      pid = fork();
      if (pid == 0) /* child process */
      {
        if (find(newVec[i].begin(), newVec[i].end(), key) != newVec[i].end())
        {
          exit(0); //key is found
        }
        else
        {
          exit(1); //key is not found
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
      int exit_status;
      int count = 0; // check to see if exit(1) is found
      for (int i = 0; i < numProcesses; ++i)
      {/* parent calls wait () n times (numProcesses) */
        if (wait(&exit_status) < 1)
        {
          perror("wait");
          exit(-1);
        }
        if (WEXITSTATUS(exit_status) == 0)
        {
          printf("The string is found!\n");
        }
        if (WEXITSTATUS(exit_status) == 1)
        {
          ++count;
        }
      }

      if (count == numProcesses)
      {
        printf("No string found!\n");
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

// source: "https://www.techiedelight.com/split-vector-into-subvectors-cpp/"
// for the next and copy functions used in splitting the vector into n sections
