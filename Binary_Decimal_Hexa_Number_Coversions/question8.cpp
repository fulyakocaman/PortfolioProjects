#include "question8.hpp"
#include <cmath>
#include <ctype.h>
#include <iostream>
#include <string>

// This function converts a binary integer string into an integer value
int binary_to_decimal(const std::string &bin_num) {
  int decimal_num = 0;
  const int base_two = 2;

  // Starting the loop with the last element of the string that will match with
  // the least significant digit of the binary number which corresponds to 2^0
  for (int i = bin_num.size() - 1; i >= 0; i--) {
    // Needed to subtract 48 from each element in the string based on their
    // ASCII value in order to covert them to the integers 0 and 1
    decimal_num +=
        ((bin_num[i] - 48) * pow(base_two, (bin_num.size() - 1) - i));
  }

  return decimal_num;
}

// This function converts an integer value into a binary integer string
std::string decimal_to_binary(int decimal_num) {
  std::string binary_num = "";
  const int base_two = 2;
  // Using an array of 2 binary characters with index from 0-1
  char binary_arry[] = {'0', '1'};

  // Exacuting the loop while the decimal_num (the quotient) is greater than 0
  while (decimal_num > 0) {
    int i = 0;
    // i is the remainder after dividing the decimal_num (the quotient) by 2
    i = decimal_num % base_two;
    // After getting the remainder i and matching it with the ith binary_arry
    // character, then put it at the end of the binary string by adding the
    // two strings
    binary_num = binary_arry[i] + binary_num;
    // Updating the decimal_num (the quotient) after dividing by 2
    decimal_num /= base_two;
  }

  return binary_num;
}

// This function converts a hexadecimal integer string into an integer value
int hex_to_decimal(const std::string &hex_num) {
  int decimal_num = 0;
  const int base_hex = 16;

  /* Starting the loop with the last element of the string that will match with
  the least significant digit of the hex_number which corresponds to 16^0.
  Also added an if/else statement to convert hex characters into
   decimal*/
  for (int i = hex_num.size() - 1; i >= 0; i--) {
    // In this statement I had to subtract 48 from each element in the string
    // from "0" through "9" based on their ASCII value in order to covert them
    // to the integers 0-9
    if (hex_num[i] >= '0' && hex_num[i] <= '9') {
      decimal_num +=
          ((hex_num[i] - 48) * pow(base_hex, (hex_num.size() - 1) - i));
      // In this statement I had to subtract 55 from each element in the string
      // from "A" through "F" based on their ASCII value in order to covert them
      // to the integers 10-15
    } else if (hex_num[i] >= 'A' && hex_num[i] <= 'F') {
      decimal_num +=
          ((hex_num[i] - 55) * pow(base_hex, (hex_num.size() - 1) - i));
    }
  }

  return decimal_num;
}

// This function converts an integer value into a hexadecimal integer string
std::string decimal_to_hex(int decimal_num) {
  std::string hex_num = "";
  const int base_hex = 16;
  // Using an array of 16 hexadecimal characters with index from 0-15
  char hex_arry[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  // Exacuting the loop while the deceimal_num (the quotient) is greater than 0
  while (decimal_num > 0) {
    int i = 0;
    // i is the remainder after dividing the decimal_num (the quotient) by 16
    i = decimal_num % base_hex;
    // After getting the remainder i and matching with the ith hex_arry
    // character, then put it at the end of the hexadecimal string by adding the
    // two strings
    hex_num = hex_arry[i] + hex_num;
    // Updating the decimal_num (the quotient) after dividing by 16
    decimal_num /= base_hex;
  }

  return hex_num;
}

// This function converts a decimal integer string into an integer value
int decimal_num(const std::string &dec_str) {
  int decimal_num = 0;
  const int base_ten = 10;

  /* Starting the loop with the last element of the string that will match with
  the least significant digit of the dec_str which corresponds to 10^0*/
  for (int i = dec_str.size() - 1; i >= 0; i--) {
    // In this statement I had to subtract 48 from each element in the string
    // from "0" through "9" based on their ASCII value in order to covert them
    // to the integers 0-9
    decimal_num +=
        ((dec_str[i] - 48) * pow(base_ten, (dec_str.size() - 1) - i));
  }

  return decimal_num;
}

// This function converts an integer value into a decimal integer string
std::string decimal_str(int decimal_num) {
  std::string str = "";
  const int base_ten = 10;
  // Using an array of 10 decimal characters with index from 0-9
  char dec_arry[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  // Exacuting the loop while the decimal_num (the quotient) is greater than 0
  while (decimal_num > 0) {
    int i = 0;
    // i is the remainder after dividing the decimal_num (the quotient) by 10
    i = decimal_num % base_ten;
    // After getting the remainder i and matching it with the ith dec_arry
    // character, then put it at the end of the decimal string by adding the
    // two strings
    str = dec_arry[i] + str;
    // Updating the decimal_num (the quotient) after dividing by 10
    decimal_num /= base_ten;
  }

  return str;
}

/* This function calculates the value of x as a binary string after using the
 * equation X = (Y + 4) * 3 with a binary value for y*/
void calc_x_for_bin_y(const std::string &number) {
  // Restricting the unsigned number only to 0 and 1
  bool is_base_2 = true;
  for (int i = 0; i < number.size(); i++) {
    if (number[i] - '0' >= 2) {
      is_base_2 = false;
      break;
    }
  }

  if (is_base_2) { // Checks if y is a binary number str
    int num = binary_to_decimal(number); // Converts y to an integer
    int x = (num + 4) * 3; // Calculates x as an integer using the given equation
    std::cout << "The value of x after the calculation of X = (Y + 4) * 3 is "
              << decimal_to_binary(x) << "\n";
    // Finally, converts the result back to a string
  } else {
    // Gives out a statement if y is not a binary string
    std::cout << "Invalid binary value for y!\n";
  }
}

/* This function calculates the value of x as a decimal string after using the
 * equation X = (Y + 4) * 3 with a decimal value for y*/
void calc_x_for_dec_y(const std::string &number) {
  // Restricting the unsigned number only to digits from 0-9
  bool is_base_ten = true;
  for (int i = 0; i < number.size(); i++) {
    if (isdigit(number[i]) == 0) {
      is_base_ten = false;
      break;
    }
  }
  if (is_base_ten) { // Checks if y is a decimal number str
    int num = decimal_num(number); // Converts y to an integer
    int x = (num + 4) * 3; // Calculates x as an integer using the given equation
    std::cout << "The value of x after the calculation of X = (Y + 4) * 3 is "
              << decimal_str(x) << "\n";
    // Finally, converts the result back to a string
  } else {
    // Gives out a statement if y is not a decimal string
    std::cout << "Invalid decimal value for y!\n";
  }
}

/* This function calculates the value of x as a hexadecimal string after using
 * the equation X = (Y + 4) * 3 with a hexadecimal value for y*/
void calc_x_for_hex_y(const std::string &number) {
  // Restricting the unsigned number only to hexadecimal digits from 0-9 & A-F
  bool is_base_hex = true;
  for (int i = 0; i < number.size(); i++) {
    if (isxdigit(number[i]) == 0) {
      is_base_hex = false;
      break;
    }
  }
  if (is_base_hex) { // Checks if y is a hexadecimal number str
    int num = hex_to_decimal(number);  // Converts y to an integer
    int x = (num + 4) * 3; // Calculates x as an integer using the given equation
    std::cout << "The value of x after the calculation of X = (Y + 4) * 3 is "
              << decimal_to_hex(x) << "\n";
    // Finally, converts the result back to a string
  } else {
    // Gives out a statement if y is not a hexadecimal string
    std::cout << "Invalid hexadecimal value for y!\n";
  }
}
