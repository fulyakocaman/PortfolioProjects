#pragma once

#include <iostream>
#include <string>

using namespace std;

class Webpage {
private:
  string current_url_;
  size_t page_size_;

public:
  string current_url() { // getter function
    return current_url_;
  }
  size_t page_size() { // getter function
    return page_size_;
  }
  void set_current_url(string url) { // setter function
    current_url_ = url;
  }
  void set_page_size(size_t size) { // setter function
    page_size_ = size;
  }
};
