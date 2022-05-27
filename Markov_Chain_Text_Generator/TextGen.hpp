#include "sanitize.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class TextGen {
private:
  map<string, vector<string>> markov_chain;
  //(key, value) pairs. The key is a string and the value is a vector of strings

public:
  TextGen(const unsigned int seed); // Calls srand with seed as parameter
  void readIn(const string &filename);
  // Reads a file and processing the strings in it a single word at a time.
  bool isEndPunctuation(const char character);
  // Returns true if the character given as parameter is either . ? !
  vector<string> getValues(const string &key); /*Returns the value associated
  with the key if such an entry exists in the map markov_chain */
  string generateSentence(); // Returns a randomly generated sentence.
  map<string, vector<string>> get_markovChain();
  // Returns private data member associated with the class
};

// TextGen's constructor
TextGen::TextGen(const unsigned int seed) {
  srand(seed); // seeds the random number generator
}

void TextGen::readIn(const string &filename) {
  // ifstream inFile(filename);
  ifstream inFile;
  inFile.open(filename);

  string key = "^"; // previous
  string value;     // next

  if (inFile) {
    while (inFile >> value) {

      sanitize(value); // removes non-essential characters

      if (isEndPunctuation(value[value.size() - 1])) {
        string punctuation(1, value[value.size() - 1]);
        string firstpart = value.substr(0, (value.size() - 1));
        markov_chain[key].push_back(firstpart);
        markov_chain[firstpart].push_back(punctuation);
        markov_chain[punctuation].push_back("$");
        key = "^"; // reset the key to "^"
      } else {
        markov_chain[key].push_back(value);
        key = value;
      }
    }
  } else {
    throw invalid_argument("Could not open file " + filename);
  }
  inFile.close();
}

bool TextGen::isEndPunctuation(const char character) {
  char end_char[] = {'.', '?', '!'};

  for (unsigned int i = 0; i < 3; ++i) {
    if (character == end_char[i]) {
      return true;
    }
  }
  return false;
}

vector<string> TextGen::getValues(const string &key) {
  vector<string> value;
  map<string, vector<string>>::iterator it = markov_chain.find(key);
  // will search the map for the key and return an iterator to it

  if (it != markov_chain.end()) {
    value = it->second;
  }

  return value;
}

string TextGen::generateSentence() {
  string sentence = "";

  vector<string> word = getValues("^");
  // getting vector of string values of the "^" token
  unsigned int index = rand() % (word.size());
  // generates an index from 0 to word.size()-1 randomly
  string word_next = word[index];
  // picking one token word randomly from a vector
  sentence = word_next;

  while (word_next != "$") {
    sentence = sentence + " " + word_next;
    vector<string> word2 = getValues(word_next);
    // getting vector of string values of the next token
    index = rand() % (word2.size());
    word_next = word2[index];
  }

  return sentence;
}

map<string, vector<string>> TextGen::get_markovChain() { return markov_chain; }
