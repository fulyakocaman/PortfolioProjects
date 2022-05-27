#include "emergency.hpp"
#include <fstream>
#include <iostream>
#include <string>

// This function will get the address of an `Emergency` object or any of its
// derived classes and store it in the array inside `EmergencyManager`.
void EmergencyManager::add(Emergency* emergency) {
  if (size_ < 100) {
    array_[size_++] = emergency;
  }
}

// This function displays all emergencies on screen according to what the user
// has already created by calling display() member function
void EmergencyManager::display_emergencies() {
  std::cout << "Emergencies:\n\n";
  for (unsigned int i = 0; i < size_; i++) {
    array_[i]->display();
    std::cout << "\n";
  }
}

// This fuction finds the earliest Emergency and the time elapsed from the
// report time to the current time. It also displays the time elapsed and
// information about the earliest Emergency by calling display function
void EmergencyManager::show_priority_emergency(
    unsigned short int current_time) {
  Emergency* earliest = array_[0];
  unsigned short int hours = 0;
  unsigned short int minutes = 0;
  const int HRSANDMINS = 100;
  const int HR = 1;
  const int MIN = 60;
  const int DAY = 24;

  if (size_ <= 0) {
    std::cout << "No emergencies have been reported.\n";
  } else {
    // This will search through the array of report times to find the earliest
    // Emergency report time and assign it to the variable earliest
    for (unsigned int i = 0; i < size_; i++) {
      if (array_[i]->report_time() < earliest->report_time()) {
        earliest = array_[i];
      }
      // If the hour portion of the time is less than and the minute portion is
      // greater than or equal to the earliest time, in order to compute the
      // number of hours elapsed we need to take the hour portion of earliest
      // time and subtract from the hour portion of the time plus 24 hours.
      // Then, set this result to the variable hours. To compute the number of
      /// minutes elapsed we need to subtract the minute portion of the earliest
      // from the minute portion of the time. Then, set this result to the to
      // variable minutes
      if ((current_time / HRSANDMINS) <
              (earliest->report_time() / HRSANDMINS) &&
          (current_time % HRSANDMINS) >=
              (earliest->report_time() % HRSANDMINS)) {
        hours = ((current_time / HRSANDMINS) + DAY) -
                (earliest->report_time() / HRSANDMINS);
        minutes = (current_time % HRSANDMINS) -
                  (earliest->report_time() % HRSANDMINS);
      } else if ((current_time / HRSANDMINS) >=
                     (earliest->report_time() / HRSANDMINS) &&
                 (current_time % HRSANDMINS) >=
                     (earliest->report_time() % HRSANDMINS)) {
        hours = (current_time / HRSANDMINS) -
                (earliest->report_time() / HRSANDMINS);
        minutes = (current_time % HRSANDMINS) -
                  (earliest->report_time() % HRSANDMINS);
        // If the hour and the minute portions of the time are both greater than
        // or equal to the earliest time, in order to compute the number of
        // hours elapsed we need to subtract the hour portion of earliest time
        // from the hour portion of the time. Then, set this result to the
        // variable hours. To compute the number of minutes elapsed we need to
        // subtract the minute portion of the earliest from the minute portion
        // of the time. Then, set this result to the to variable minutes
      } else if ((current_time / HRSANDMINS) <
                     (earliest->report_time() / HRSANDMINS) &&
                 (current_time % HRSANDMINS) <
                     (earliest->report_time() % HRSANDMINS)) {
        hours = ((current_time / HRSANDMINS) + DAY - HR) -
                (earliest->report_time() / HRSANDMINS);
        minutes = ((current_time % HRSANDMINS) + MIN) -
                  (earliest->report_time() % HRSANDMINS);
        // If the hour and the minute portions of the time are both less than
        // the earliest time, in order to compute the number of hours elapsed we
        // need to take the hour portion of earliest time and subtract from the
        // hour portion of the time plus 24 minus 1 hours.Then, set this result
        // to the variable hours. To compute the number of minutes elapsed we
        // need to subtract the minute portion of the earliest from the minute
        // portion of the time plus 60. Then, set this result to the to variable
        // minutes
      } else {
        hours = ((current_time / HRSANDMINS) - HR) -
                (earliest->report_time() / HRSANDMINS);
        minutes = ((current_time % HRSANDMINS) + MIN) -
                  (earliest->report_time() % HRSANDMINS);
        // If the hour portion of the time is greater than or equal to and the
        // minute portion is less than the earliest time, in order to compute
        // the number of hours elapsed we need to take the hour portion of
        // earliest time and subtract from the hour portion of the time minus 1
        // hour. Then, set this result to the variable hours. To compute the
        // number of minutes elapsed we need to subtract the minute portion of
        // the earliest from the minute portion of the time plus 60. Then, set
        // this result to the to variable minutes
      }
    }
    // This will display the time elapsed in the number of hours and minutes
    // from the report time to the current time
    std::cout << "The earliest emergency was reported " << hours << " hour(s) "
              << minutes << " minute(s) ago.\n\n";

    // This function call will display the earliest Emergency
    earliest->display();
  }
}

// This function stores emergencies into a file
void EmergencyManager::save_emergencies(const std::string& filename) {
  std::ofstream out_file;
  out_file.open(filename);

  out_file << size_ << "\n";
  for (unsigned int i = 0; i < size_; i++) {
    out_file << array_[i]->save_string() << "\n";
  }

  out_file.close();

  std::cout << "File saved!\n";
}

// This function loads the file provided by the user
void EmergencyManager::load_emergencies(const std::string& filename) {
  std::ifstream in_file;
  in_file.open(filename);
  std::string emergency_type;
  std::string line_description;
  std::string line_other_emergencies;
  std::string line_location;
  unsigned short int estimated_time_read = 0;
  unsigned short int time_read = 0;

  if (in_file) {
    in_file >> size_;
    in_file.ignore();

    for (unsigned int i = 0; i < size_; i++) {
      std::getline(in_file, emergency_type);
      if (emergency_type == "[Emergency]") {
        Emergency* obj = new Emergency;
        std::getline(in_file, line_description);
        obj->set_description(line_description);
        std::getline(in_file, line_location);
        obj->set_location(line_location);
        in_file >> time_read;
        in_file.ignore();
        obj->set_report_time(time_read);
        array_[i] = obj;
      } else if (emergency_type == "[MultipleEmergency]") {
        MultipleEmergency* obj = new MultipleEmergency;
        std::getline(in_file, line_description);
        obj->set_description(line_description);
        std::getline(in_file, line_other_emergencies);
        obj->set_other_emergencies(line_other_emergencies);
        std::getline(in_file, line_location);
        obj->set_location(line_location);
        in_file >> time_read;
        in_file.ignore();
        obj->set_report_time(time_read);
        array_[i] = obj;
      } else if (emergency_type == "[PotentialEmergency]") {
        PotentialEmergency* obj = new PotentialEmergency;
        std::getline(in_file, line_description);
        obj->set_description(line_description);
        std::getline(in_file, line_location);
        obj->set_location(line_location);
        in_file >> estimated_time_read;
        obj->set_estimated_time(estimated_time_read);
        in_file >> time_read;
        obj->set_report_time(time_read);
        in_file.ignore();
        array_[i] = obj;
      }
    }
    std::cout << "File loaded!\n";

  } else {
    std::cout << "File does not exist.\n";
  }

  in_file.close();
}

// This function gets the data from the user and returns the address of a
// dynamically allocated `Emergency` object
Emergency* create_emergency() {
  std::string description;
  std::string location;
  unsigned short int report_time = 0;

  std::cout << "Please describe the emergency: ";
  std::getline(std::cin, description);

  std::cout << "Provide the location of the emergency: ";
  std::getline(std::cin, location);

  std::cout << "Please enter the time that emergency was reported: ";
  std::cin >> report_time;
  std::cin.ignore();

  // Create Emergency object that returns user's input
  Emergency* my_emergency = new Emergency;
  my_emergency->set_description(description);
  my_emergency->set_location(location);
  my_emergency->set_report_time(report_time);

  return my_emergency;
  delete my_emergency;
  my_emergency = nullptr;
}

// This function gets the data from the user and returns a pointer to a
// dynamically allocated `MultipleEmergency` object using the values provided by
// the user
MultipleEmergency* create_multiple_emergency() {
  std::string description;
  std::string other_emergencies;
  std::string location;
  unsigned short int report_time = 0;

  std::cout << "Please describe the emergency: ";
  std::getline(std::cin, description);

  std::cout << "Please provide other co-occurring emergencies: ";
  std::getline(std::cin, other_emergencies);

  std::cout << "Provide the location of the emergency: ";
  std::getline(std::cin, location);

  std::cout << "Please enter the time that emergency was reported: ";
  std::cin >> report_time;
  std::cin.ignore();

  // Create MultipleEmergency object that returns user's input
  MultipleEmergency* multiple_emergency = new MultipleEmergency;
  multiple_emergency->set_description(description);
  multiple_emergency->set_other_emergencies(other_emergencies);
  multiple_emergency->set_location(location);
  multiple_emergency->set_report_time(report_time);

  return multiple_emergency;
  delete multiple_emergency;
  multiple_emergency = nullptr;
}

// This function gets the data from the user and returns a pointer to a
// dynamically allocated `PotentialEmergency` object using the values provided
// by the user
PotentialEmergency* create_potential_emergency() {
  std::string description;
  std::string location;
  unsigned short int estimated_time = 0;
  unsigned short int report_time = 0;

  std::cout << "Please describe the emergency: ";
  std::getline(std::cin, description);

  std::cout << "Provide the location of the emergency: ";
  std::getline(std::cin, location);

  std::cout << "Please provided the estimated time that emergency: ";
  std::cin >> estimated_time;

  std::cout << "Please enter the time that emergency was reported: ";
  std::cin >> report_time;
  std::cin.ignore();

  // Create PotentialEmergency object that returns user's input
  PotentialEmergency* potential_emergency = new PotentialEmergency;
  potential_emergency->set_description(description);
  potential_emergency->set_location(location);
  potential_emergency->set_estimated_time(estimated_time);
  potential_emergency->set_report_time(report_time);

  return potential_emergency;
  delete potential_emergency;
  potential_emergency = nullptr;
}
// This menu-based function asks the user to choose between four options
void display_menu() {
  std::cout << "What do you want to do? "
            << "\n";
  std::cout << "E - Report an emergency"
            << "\n";
  std::cout << "M - Report multiple emergencies"
            << "\n";
  std::cout << "O - Report potential emergencies"
            << "\n";
  std::cout << "D - Display emergencies"
            << "\n";
  std::cout << "P - Show prority emergency"
            << "\n";
  std::cout << "S - Save emergencies"
            << "\n";
  std::cout << "L - Load emergencies"
            << "\n";
  std::cout << "X - Exit"
            << "\n";
  std::cout << "Action: ";
}

// This function asks the user to provide the current time
unsigned short int get_current_time() {
  unsigned short int current_time = 0;
  std::cout << "Please enter the current time: ";
  std::cin >> current_time;
  std::cin.ignore(); // Added this according to the instructor's solutions
  return current_time;
}

// Asking the user to provide the file name to save the emergencies
std::string get_filename() {
  std::string filename = " ";
  std::cout << "Please enter the filename: ";
  std::cin >> filename;
  std::cin.ignore(); // Added this according to the instructor's solutions

  return filename;
}
