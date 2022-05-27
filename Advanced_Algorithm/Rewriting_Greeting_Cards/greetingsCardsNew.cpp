#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

/**
 * Function returns a string in a file
 * @param fileName - the argument
 */
string getStr(const string &fileName) {
  // Stores the sentence read from a file
  string sentence;

  ifstream fileS(fileName);

  if (fileS) {
    getline(fileS, sentence);
  } else {
    fprintf(stderr, "Could not open the file!");
  }

  fileS.close();

  return sentence;
}

/**
 * Function returns pairs of words in a file
 * @param fileName - the argument
 */
map<string, string> getStringPairs(const string &fileName) {
  // Stores each sentence read from a file
  string sentenceRead;

  // Counts the number of lines read from a file
  int numLineRead = 0;

  int index = 1;

  /*(key, value) pairs. The key is a string to be replaced the value is the
  actual string replacement */
  map<string, string> pairs;

  string key;   // a string to be replaced
  string value; // the actual string replacement

  ifstream fileLS(fileName);

  if (fileLS) {
    while (getline(fileLS, sentenceRead)) {
      key = sentenceRead;
      if (numLineRead % 2 == 0) {
        getline(fileLS, sentenceRead);
        value = sentenceRead;
        index++;
      }
      pairs[key] = value;
    }
  } else {
    fprintf(stderr, "Could not open the file!");
  }

  fileLS.close();

  return pairs;
}

int main(int argc, char **argv) {
  // Sanity check -- make sure the user provided all of the required arguments
  if (argc < 3) {
    fprintf(stderr,
            "USAGE: %s <StringS FILE NAME> <StringPairsLS FILE NAME> \n",
            argv[0]);
    exit(1);
  }

  // Stores the file name of the input string S
  string stringSFileName = argv[1];

  // Stores the file name of the input pairs of string LS
  string stringPairsLSFileName = argv[2];

  // Pairs of strings read from the stringPairsLS file
  map<string, string> stringPairsLS = getStringPairs(stringPairsLSFileName);

  string originalStr = getStr(stringSFileName);

  //  stores the index of the first occurrence of the string
  vector<int> foundVec;
  //  stores the string that needs to be replaced
  vector<string> foundStr;

  /*
  Goes through each pair and finds the index and string that needs to be
  replaced in the sentence. Stores the indexes in foundVec and strings in
  foundStr vectors respectively
  */
  for (auto &it : stringPairsLS) {
    // Finding the first occurrence of the key
    size_t found = originalStr.find(it.first);

    if (found != string::npos) {
      foundVec.push_back(found);
      foundStr.push_back(originalStr.substr(found, it.first.length()));
    }
    while (found != string::npos) {
      found = originalStr.find(it.first, (found + (it.second.length())));
      if (found != string::npos) {
        foundVec.push_back(found);
        foundStr.push_back(originalStr.substr(found, it.first.length()));
      }
    }
  }

  /*
  Uses a simple Buble Sort to reversely sort the index vector along with the
  string vector so that the replacement would happen starting from the end of
  the sentece not from the begining to avoid replacing the word twice
  */
  int temp;
  string temp2;
  for (int k = 1; k < foundVec.size(); k++) {
    for (int i = 0; i < foundVec.size() - k; i++) {
      if (foundVec[i] < foundVec[i + 1]) {
        temp = foundVec[i + 1];
        foundVec[i + 1] = foundVec[i];
        foundVec[i] = temp;
        temp2 = foundStr[i + 1];
        foundStr[i + 1] = foundStr[i];
        foundStr[i] = temp2;
      }
    }
  }

  std::map<string, string>::iterator it2;

  /*
  loops through each foundStr vector anf if a string is found in a pair,
  replaces with the pair's value in the sentence
  */
  for (int j = 0; j < foundStr.size(); j++) {
    it2 = stringPairsLS.find(foundStr[j]);
    if (it2 != stringPairsLS.end()) {
      originalStr.replace(foundVec[j], it2->first.length(), it2->second);
    }
  }

  fprintf(stderr, "%s\n", originalStr.c_str());

  return 0;
}
