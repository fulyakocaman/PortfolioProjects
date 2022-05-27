#include "emergency.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main() {
  EmergencyManager object;
  char action = ' ';
  unsigned short int time = 0;
  std::string file_name = " ";

  std::cout << "Welcome to TuffyAid Emergency Response!\n\n";

  do {
    display_menu(); // Calling display_menu function
    std::cin >> action;
    std::cout << "\n";
    std::cin.ignore();

    if (action == 'E' || action == 'e') {
      object.add(create_emergency());
      // Calling create_emergency function in order to store the user's input
      // inside add function of the EmergencyManager object
    } else if (action == 'M' || action == 'm') {
      object.add(create_multiple_emergency());
      // Calling create_multiple_emergency function in order to store the user's
      // input inside add function of the EmergencyManager object
    } else if (action == 'O' || action == 'o') {
      object.add(create_potential_emergency());
      // Calling create_potential_emergency function in order to store the
      // user's input inside add function of the EmergencyManager object
    } else if (action == 'D' || action == 'd') {
      object.display_emergencies();
      // Calling the object's display_emergencies function to display all
      // emergencies
    } else if (action == 'P' || action == 'p') {
      time = get_current_time();
      // Calling get_current_time function and setting it equal to current_time
      // to store the user's time input
      object.show_priority_emergency(time);
      // Calling the object's show_priority_emergency function to get the
      // earliest Emergency and the time elapsed from the report time to the
      // current time
    } else if (action == 'S' || action == 's') {
      file_name = get_filename();
      // Calling get_filename function and setting it equal to file_name
      // to store the user's time input
      object.save_emergencies(file_name);
      // Calling the object's save_emergencies function to store emergencies
      // into a file
    } else if (action == 'L' || action == 'l') {
      file_name = get_filename();
      // Calling get_filename function and setting it equal to file_name
      // to store the user's time input
      object.load_emergencies(file_name);
      // Calling the object's load_emergencies function to load the file
    }
    std::cout << "\n";
  } while ((action != 'x') && (action != 'X'));
  std::cout << "Thank you for using TuffyAid Emergency Response!\n";

  return 0;
}
