#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

/**
 * Function returns the number of words in a file
 * @param fileName - the argument
 */
int numWords(const string &fileName) {
  int num = 1;
  string sentenceRead;
  ifstream file(fileName);

  if (file) {
    while (!file.eof()) {
      getline(file, sentenceRead);
      ++num;
    }
  } else {
    fprintf(stderr, "Could not open the file!\n");
  }

  file.close();

  return num;
}

/**
 * Function returns pairs of words from the word frequency file
 * @param fileName - the argument
 */
vector<pair<string, int>> getWordFreqPairs(const string &fileName,
                                           int wordSize) {
  // Stores each sentence read from a file
  string sentenceRead;

  /*(key, value) pairs. The key is a string and the value is its corresponding
  frequency */
  vector<pair<string, int>> vecPairs;

  string key[wordSize];
  int value[wordSize]; // corresponding frequency of the string

  ifstream file1(fileName);

  if (file1) {
    for (int i = 0; i < wordSize - 1; ++i) {
      getline(file1, sentenceRead);
      key[i] = sentenceRead;
      getline(file1, sentenceRead);
      value[i] = stoi(sentenceRead);
      vecPairs.push_back(make_pair(key[i], value[i]));
    }
  } else {
    fprintf(stderr, "Could not open the file!");
  }

  file1.close();

  return vecPairs;
}

/**
 * Function returns pairs of words from the synonyms file
 * @param fileName - the argument
 */
vector<pair<string, string>> getStringPairs(const string &fileName,
                                            int wordSize) {
  // Stores each sentence read from a file
  string sentenceRead;

  /*(key, value) pairs. The key is a string and the value is its synonym */
  vector<pair<string, string>> vecPairs;

  string key[wordSize];
  string value[wordSize]; // corresponding synonym string

  ifstream file2(fileName);

  if (file2) {
    for (int i = 0; i < wordSize - 1; ++i) {
      getline(file2, sentenceRead);
      key[i] = sentenceRead;
      getline(file2, sentenceRead);
      value[i] = sentenceRead;
      vecPairs.push_back(make_pair(key[i], value[i]));
    }

  } else {
    fprintf(stderr, "Could not open the file!");
  }

  file2.close();

  return vecPairs;
}

/**
 * Function prints original pairs of words with their frequencies
 * @param wordFreq - the argument
 */
void printFreqPairs(vector<pair<string, int>> wordFreq) {

  for (auto &it : wordFreq) {
    cout << "[name: " << it.first << "] = " << it.second << "\n";
  }

  cout << "\nsize of word frequency pairs = " << wordFreq.size() << endl;
  cout << "---------------------------------------------------------\n";
}

/**
 * Function prints original pairs of words with their synonyms
 * @param synonyms - the argument
 */
void printSynonymsPairs(vector<pair<string, string>> synonyms) {

  for (auto &it : synonyms) {
    cout << "[name: " << it.first << "] = " << it.second << "\n";
  }

  cout << "\nsize of synonyms pairs = " << synonyms.size() << endl;

  cout << "---------------------------------------------------------\n";
}


int main(int argc, char **argv) {
  // Sanity check -- make sure the user provided all of the required arguments
  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <wordFreq FILE NAME> <synonyms FILE NAME> \n",
            argv[0]);
    exit(1);
  }

  // Stores the file name of the input pairs of words and their frequencies
  string wordFreqFileName = argv[1];

  // Stores the file name of the input pairs of synonyms
  string synonymsFileName = argv[2];

  // The size of the vector of words
  int size1 = numWords(wordFreqFileName) / 2;

  // The size of the vector of words
  int size2 = numWords(synonymsFileName) / 2;

  // Vector of strings read from the stringS file
  vector<pair<string, int>> wordFreqVec =
      getWordFreqPairs(wordFreqFileName, size1);

  // Vector of strings read from the stringS file
  vector<pair<string, string>> synonymsVec =
      getStringPairs(synonymsFileName, size2);

  // prints the original word frequency pairs
  printFreqPairs(wordFreqVec);

  // prints the original word synonyms pairs
  printSynonymsPairs(synonymsVec);

  // creates unique word frequency pairs
  for (int k = 0; k < wordFreqVec.size() - 1; k++) {
    for (int i = k + 1; i < wordFreqVec.size(); i++) {
      if ((wordFreqVec[k].first == wordFreqVec[i].first) &&
          (wordFreqVec[k].second == wordFreqVec[i].second)) {
        wordFreqVec.erase(wordFreqVec.begin() + i);
      }
    }
  }

  // creates unique word synonym pairs
  for (int k = 0; k < synonymsVec.size() - 1; k++) {
    for (int i = k + 1; i < synonymsVec.size(); i++) {
      if ((synonymsVec[k].first == synonymsVec[i].first) &&
          (synonymsVec[k].second == synonymsVec[i].second)) {
        synonymsVec.erase(synonymsVec.begin() + i);
      }
    }
  }

  // creates an adjacency matrix
  vector<vector<string>> adjMatrix;

  adjMatrix.resize(wordFreqVec.size());

  // populates the adjacency matrix with rows from wordFreqVec
  for (int k = 0; k < wordFreqVec.size(); k++) {
    adjMatrix[k].push_back(wordFreqVec[k].first);
    // Now, in the adj matrix each row populated with wordFreq names
  }

  // adds edges to wordFreqVec from synonym pairs
  for (int j = 0; j < synonymsVec.size(); j++) {
    // outer loop index j for the each synonym from synonymsVec
    for (int i = 0; i < wordFreqVec.size(); i++) {
      // inner loop index i for the rows of the adj matrix
      if (adjMatrix[i][0] == synonymsVec[j].first) {
        // add an edge to the matching synonym word
        for (int k = 0; k < adjMatrix.size(); k++) {
          // find the word corresponding to the to the matching synonym word
          // to add an edge symmetrically, so index k keeps track of the
          // corresponding synonym word
          if (adjMatrix[k][0] == synonymsVec[j].second) {
            int index = adjMatrix[k].size();
            for (int m = 0; m < index; m++) {
              // adds an adge to the matching synonym word
              adjMatrix[k].push_back(adjMatrix[i][m]);
              // adds an adge to the matching  word
              adjMatrix[i].push_back(adjMatrix[k][m]);
            }
            break;
          }
        }
        break;
      }
    }
  }


  // removes repeating words in the adjacency matrix if any
  for (int m = 0; m < adjMatrix.size(); m++) {
    // outer loop index m for the row of adjMatrix
    for (int k = 0; k < adjMatrix[m].size() - 1; k++) {
      // index k keeps track of the first word of each row m
      for (int i = k + 1; i < adjMatrix[m].size(); i++) {
        // index i keeps track of the next word of each row m to compare if they
        // are the same
        if (adjMatrix[m][k] == adjMatrix[m][i]) {
          // if same, remove the next word from that row
          adjMatrix[m].erase(adjMatrix[m].begin() + i);
        }
      }
    }
  }

  // sorts the words in each row of the adjMatrix
  for (int i = 0; i < adjMatrix.size(); i++) {
    std::sort(adjMatrix[i].begin(), adjMatrix[i].end());
  }

  // sorts the rows of the adjMatrix
  std::sort(adjMatrix.begin(), adjMatrix.end());

  // removes the same rows if there is any
  adjMatrix.erase(std::unique(adjMatrix.begin(), adjMatrix.end()),
                  adjMatrix.end());

  // removes the rows that are subsets of the other rows which have at least
  // one common word
  for (int k = 0; k < adjMatrix.size() - 1; k++) {
    // outer loop index k for the row of adjMatrix
    for (int m = 0; m < adjMatrix[k].size(); m++) {
      // index m to keep track for each row m
      for (int i = k + 1; i < adjMatrix.size(); i++) {
        // index i for the next row after row k
        for (int j = 0; j < adjMatrix[i].size(); j++) {
          // index j to keep track for each row j
          if ((adjMatrix[k][m] == adjMatrix[i][j]) &&
              (adjMatrix[k].size() > adjMatrix[i].size())) {
            // if they have a common word and size of row k > size of row i,
            // removes row i
            adjMatrix.erase(adjMatrix.begin() + i);
            break;
          }

          if ((adjMatrix[k][m] == adjMatrix[i][j]) &&
              (adjMatrix[k].size() < adjMatrix[i].size())) {
            // if they have a common word and size of row k < size of row i,
            // removes row k
            adjMatrix.erase(adjMatrix.begin() + k);
            break;
          }
        }
      }
    }
  }


  cout << "The cumulative frequencies: \n";
  // keep track of each cumulative frequency of similar groups of words
  int count = 0;

  for (int i = 0; i < adjMatrix.size(); i++) {
    // outer loop index i for the row of adjMatrix
    for (auto it1 = adjMatrix[i].begin(); it1 != adjMatrix[i].end(); it1++) {
      // iterator 1 goes through each row of the adjMatrix
      for (auto &it2 : wordFreqVec) {
        // iterator 2 goes through each row of wordFreqVec
        if (*it1 == it2.first)
        // if finds a match, adds up to the grand total
          count += it2.second;
      }
    }
    // print the first word from each sorted similar row along with each group's
    // cumulative frequency in a sorted fashion
    cout << adjMatrix[i][0] << " = " << count << endl;
    count = 0;
  }

  return 0;
}
