///////////////////////////////////////////////////////////////////////////////
// subsequence.hpp
//
// An exhaustive optimization algorithm for solving
// the longest increasing subsequence problem.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using sequence = std::vector<int>;

// Convert a sequence into a human-readable string useful for pretty-printing
// or debugging.
std::string sequence_to_string(const sequence &seq) {
  std::stringstream ss;
  ss << "[";
  bool first = true;
  for (auto &x : seq) {
    if (!first) {
      ss << ", ";
    }
    ss << x;
    first = false;
  }
  ss << "]";
  return ss.str();
}

// Generate a pseudorandom sequence of the given size, using the given
// seed, where all elements are in the range [0, max_element]. max_element
// must be non-negative.
sequence random_sequence(size_t size, unsigned seed, int max_element) {

  assert(max_element >= 0);

  sequence result;

  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dist(0, max_element);

  for (size_t i = 0; i < size; ++i) {
    result.push_back(dist(gen));
  }

  return result;
}

bool is_increasing(const sequence &A) {
  for (size_t i = 1; i < A.size(); ++i) {
    if (A[i - 1] >= A[i]) {
      return false;
    }
  }
  return true;
}

sequence longest_increasing_powerset(const sequence &A) {
  const size_t n = A.size();
  sequence increasing_best; // stores the increasing candidates
  sequence best;            // stores the longest increasing candidate
  size_t best_length = 0;
  std::vector<size_t> stack(n + 1, 0); // allocate space for the set
  size_t k = 0;

  while (true) {

    if (stack[k] < n) {
      stack[k + 1] = stack[k] + 1;
      ++k;
    } else {
      stack[k - 1]++;
      k--;
    }

    if (k == 0) {
      break;
    }

    // Generating the power set and storing them in candidate vector
    sequence candidate;
    for (size_t i = 1; i <= k; ++i) {
      candidate.push_back(A[stack[i] - 1]);
    }

    if (k > best_length) {
      bool increasing = true;
      size_t i = 0;

      if (k == 1) { // empty set, not increasing. Do not do comparison!

        // verifying the candidates; check to see if any increasing
      } else {
        while (increasing && i < (k - 1)) {
          if (candidate[i] >= candidate[i + 1]) {
            increasing = false; // exits the loop when there is a single
          }                     // false comparison
          i++;
        }
      }

      // comparing the candidates; if increasing, select the longest size
      if (increasing) {
        best_length = k;
        for (size_t i = 0; i < best_length; i++) {
          increasing_best.push_back(candidate[i]);
        }
      }
    }
  }
  // storing only the longest sequence in the best starting from the best length
  // size of the increasing_best sequence
  for (size_t i = (increasing_best.size() - best_length);
       i < increasing_best.size(); i++) {
    best.push_back(increasing_best[i]);
  }

  return best;
}
