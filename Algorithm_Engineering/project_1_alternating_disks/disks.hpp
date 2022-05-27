///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream> //for std::stringstream
#include <string>
#include <vector>

// State of one disk, either light or dark.
enum disk_color { DISK_LIGHT, DISK_DARK };

// Data structure for the state of one row of disks.
class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count) : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 0; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  // Equality operator for unit tests.
  bool operator==(const disk_state &rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const { return _colors.size(); }

  size_t light_count() const { return total_count() / 2; }

  size_t dark_count() const { return light_count(); }

  bool is_index(size_t i) const { return (i < total_count()); }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }
      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is dark, the second disk at index 1
  // is light, and so on for the entire row of disks.
  bool is_alternating() const {
    bool check = false;

    // Changed the while to for loop for more accurate step counting
    for (int i = 0; i < light_count(); i++) {
      if (_colors[2 * i] == DISK_DARK && _colors[2 * i + 1] == DISK_LIGHT) {
        check = true;
      }
    }

    /* Or checking the disk by one by one could work
    for (int i = 0; i < total_count() - 1; i++) {
      if (_colors[i] == DISK_DARK && _colors[i + 1] == DISK_LIGHT) {
        check = true;
      }
    }*/

    /* Or checking using the while loop could work
    int i = 0;
    while (_colors[i] == DISK_DARK && _colors[i + 1] == DISK_LIGHT &&
           i < total_count() - 1) {
      check = true;
      i++;
    }*/

    return check;
  }

  // Return true when this disk_state is fully sorted, with all light disks
  // on the left (low indices) and all dark disks on the right (high
  // indices).
  bool is_sorted() const {
    bool check = false;

    int i = 0;
    // checking only the light disks from 1 to n would be sufficient to see if
    // this disk_state is fully sorted
    while (_colors[i] == DISK_LIGHT && i < light_count()) {
      check = true;
      i++;
    }

    return check;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:
  sorted_disks(const disk_state &after, unsigned swap_count)
      : _after(after), _swap_count(swap_count) {}

  sorted_disks(disk_state &&after, unsigned swap_count)
      : _after(after), _swap_count(swap_count) {}

  const disk_state &after() const { return _after; }

  unsigned swap_count() const { return _swap_count; }
};

// Algorithm that sorts disks using the left-to-right algorithm.
sorted_disks sort_left_to_right(const disk_state &before) {
  // m is the number of swaps to move the dark ones after the light ones
  unsigned int m = 0;
  disk_state after = before;

  if (after.is_alternating()) { // if the disks are alternating
    for (int i = 0; i < after.light_count(); i++) {
      // Once it reaches the right-hand end, it goes back to the leftmost disk n
      // times
      for (int j = i; j < after.total_count() - i - 1; j++) {
        // after learning the bubble sort, changed it to 2n-i-1 to avoid
        // unnecessary comparisons
        if (after.get(j) == DISK_DARK && after.get(j + 1) == DISK_LIGHT) {
          after.swap(j);
          m++; // start counting the swaps right after each swap
        }
      }
    }
  }

  sorted_disks sort(after, m);
  return sort;
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state &before) {
  // m is the number of swaps to move the dark ones after the light ones
  unsigned int m = 0;
  disk_state after = before;

  if (after.is_alternating()) { // if the disks are alternating
    // Once it reaches the right-hand end, it starts with the disk before the
    // rightmost disk and proceeds to the left ⌈n/2⌉ times.
    for (int i = 0; i < after.light_count() / 2 + 1; i++) {
      // proceeding to the right-hand end
      for (int j = i; j < after.total_count() - i - 1; j++) {
        // after learning the bubble sort, changed it to 2n-i-1 to avoid
        // unnecessary comparisons
        if (after.get(j) == DISK_DARK && after.get(j + 1) == DISK_LIGHT) {
          after.swap(j);
          m++; // start counting the swaps right after each swap
        }
      }
      // proceeding to the left-hand end
      for (int j = after.total_count() - i - 1; j > i; j--) {
        // after learning the bubble sort, changed it to 2n-i-1 to avoid
        // unnecessary comparisons
        if (after.get(j) == DISK_LIGHT && after.get(j - 1) == DISK_DARK) {
          after.swap(j - 1);
          m++; // start counting the swaps right after each swap
        }
      }
    }
  }

  sorted_disks sort(after, m);
  return sort;
}
