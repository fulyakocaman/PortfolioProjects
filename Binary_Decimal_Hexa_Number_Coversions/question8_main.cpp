#include "question8.hpp"
#include <string>

int main() {
  std::string num = "";
  char action = ' ';

  std::cout
      << "Welcome to the online calculator that calculates X = (Y + 4) * 3 "
         "for any y that is a binary or a decimal or a hexadecimal!\n\n";
  /* Asking the user to determine whether a particular string of digits was
   * meant to be a binary or a decimal or a hexadecimal representation*/
  do {
    std::cout << "Please choose your y:\n";
    std::cout << "B - y as a binary string\n";
    std::cout << "D - y as a decimal string\n";
    std::cout << "H - y as a hexadecimal string\n";
    std::cout << "X - Exit\n";
    std::cout << "Action: ";
    std::cin >> action;
    std::cin.ignore();

    if (action == 'B' || action == 'b') {
      // Asking the user for a value of y as a binary string
      std::cout << "Enter a value for y: ";
      std::cin >> num;
      // Calling the calc_x_for_bin_y function to calculate x for the y
      calc_x_for_bin_y(num);
    } else if (action == 'D' || action == 'd') {
      // Asking the user for a value of y as a decimal string
      std::cout << "Enter a value for y: ";
      std::cin >> num;
      // Calling the calc_x_for_dec_y function to calculate x for the y
      calc_x_for_dec_y(num);
    } else if (action == 'H' || action == 'h') {
      // Asking the user for a value of y as a hexadecimal string
      std::cout << "Enter a value for y: ";
      std::cin >> num;
      // Calling the calc_x_for_hex_y function to calculate x for the y
      calc_x_for_hex_y(num);
    }
    std::cout << "\n";
  } while (action != 'x' && action != 'X');
  std::cout << "Thank you for using online calculator!\n";

  return 0;
}
