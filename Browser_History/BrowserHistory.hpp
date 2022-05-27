#pragma once

#include "Webpage.hpp"
#include <fstream>
#include <iostream>
#include <iterator> // std::next, std::prev
#include <list>
#include <string>

using std::string;
// using namespace std;

class BrowserHistory {
public:
  BrowserHistory(); // Default constructor

  void visitSite(string url, size_t filesize);
  /* user visits a webpage with the given URL and web page size (in number of
   * bytes).*/
  void backButton();
  /*current webpage changes to the previous one in the visit sequence. If there
   * is no previous page, current web page stays the same*/
  void forwardButton();
  /*current webpage changes to the next one in the visit sequence. If there is
   * no such page, current web page stays the same*/

  // read from file
  void readFile(string fileName);
  // BrowserHistory should return the current webpage’s url and pagesize via
  // these methods:
  string currentUrl();
  /*Returns the current url. If there is no webpage in the history, the function
   * returns the empty string.*/
  size_t currentPageSize();
  /*Returns the current webpage’s page size. If there is no webpage in the
   * history, the function returns 0.*/
  size_t getHistoryLength();
  /*returns the length of the webpage history.*/
private:
  list<Webpage> webpage_list;
  list<Webpage>::iterator it;
};

BrowserHistory::BrowserHistory() {}

void BrowserHistory::visitSite(string url, size_t filesize) {
  // Removes the part of the browsing history forward of the current webpage
  if (webpage_list.size() > 1) {
    webpage_list.erase(next(it), webpage_list.end());
  }
  Webpage new_page;
  new_page.set_current_url(url);
  new_page.set_page_size(filesize);

  webpage_list.push_back(new_page);
  it = prev(webpage_list.end());
}

void BrowserHistory::backButton() {
  if (it != webpage_list.begin()) {
    it--;
  } else {
    cout << "There is no previous page" << endl;
  }
}

void BrowserHistory::forwardButton() {
  if (it != prev(webpage_list.end())) {
    it++;
  } else {

    cout << "There is no page to move forward to." << endl;
  }
}

void BrowserHistory::readFile(string fileName) {
  ifstream inFile;
  string word_read;
  inFile.open(fileName); // Open the input file
  // if (in_file) {                          // If the file opens, read it
  while (inFile >> word_read) {
    if (word_read == "visit") {
      string url;
      size_t size;
      inFile >> url;
      inFile >> size;
      visitSite(url, size);
      inFile.ignore();
    } else if (word_read == "back") {
      backButton();
    } else if (word_read == "forward") {
      forwardButton();
    }
  }
  // } else {throw invalid_argument("Could not open file " + fileName);}
  inFile.close();
}

string BrowserHistory::currentUrl() {
  if (webpage_list.empty()) {
    return "";
  } else {
    return it->current_url();
  }
}

size_t BrowserHistory::currentPageSize() {
  if (webpage_list.empty()) {
    return 0;
  } else {
    return it->page_size();
  }
}

size_t BrowserHistory::getHistoryLength() { return webpage_list.size(); }
