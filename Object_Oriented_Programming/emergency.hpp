// Emergency.hpp is the Emergency class specification file
#include <iostream>
#include <string>

// Emergency class declaration
class Emergency {
private: // Member variables
  std::string description_;
  std::string location_;
  unsigned short int report_time_;

public:
  // Default constructor
  Emergency() : Emergency("None", "None", 800) {}
  // Non-default constructor
  Emergency(const std::string& description, const std::string& location,
            unsigned short int report_time)
      : description_(description), location_(location),
        report_time_(report_time) {}

  // Accessors
  void set_description(const std::string& description) {
    description_ = description;
  }
  void set_location(const std::string& location) { location_ = location; }
  void set_report_time(unsigned short int report_time) {
    report_time_ = report_time;
  }

  // Mutators
  std::string description() { return description_; }
  std::string location() { return location_; }
  unsigned short int report_time() { return report_time_; }

  // This member function displays information about the emergency
  virtual void display() {
    std::cout << "Emergency: " << description_ << "\n";
    std::cout << "Location: " << location_ << "\n";
    std::cout << "Report time: " << report_time_ << "\n";
  }

  // This member function is used for file saving, wherein it returns an
  // `std::string` to contain the text `"[Emergency]"` on the first line
  // followed by the name of the emergency, its location and report_time.
  virtual std::string save_string() {
    return "[Emergency]\n" + description_ + "\n" + location_ + "\n" +
           std::to_string(report_time_);
  }
};

// MultipleEmergency class declaration
class MultipleEmergency : public Emergency {
private: // Member variable
  std::string other_emergencies_;

public:
  // Default constructor
  MultipleEmergency() : MultipleEmergency("None", "None", "None", 800) {}
  // Non-default constructor
  MultipleEmergency(const std::string& description,
                    const std::string& other_emergencies,
                    const std::string& location, unsigned short int report_time)
      : Emergency(description, location, report_time),
        other_emergencies_(other_emergencies) {}

  // Accessor
  void set_other_emergencies(const std::string& other_emergencies) {
    other_emergencies_ = other_emergencies;
  }

  // Mutator
  std::string other_emergencies() { return other_emergencies_; }

  // This member function overrides Emergency's implementation
  void display() override {
    std::cout << "Emergency: " << description() << "\n";
    std::cout << "Other Emergencies: " << other_emergencies_ << "\n";
    std::cout << "Location: " << location() << "\n";
    std::cout << "Report time: " << report_time() << "\n";
  }

  // This member function overrides Emergency's implementation
  std::string save_string() override {
    return "[MultipleEmergency]\n" + description() + "\n" + other_emergencies_ +
           "\n" + location() + "\n" + std::to_string(report_time());
  }
};

// PotentialEmergency class declaration
class PotentialEmergency : public Emergency {
private: // Member variable
  unsigned short int estimated_time_;

public:
  // Default constructor
  PotentialEmergency() : PotentialEmergency("None", "None", 1000, 800) {}
  // Non-default constructor
  PotentialEmergency(const std::string& description,
                     const std::string& location,
                     unsigned short int estimated_time,
                     unsigned short int report_time)
      : Emergency(description, location, report_time),
        estimated_time_(estimated_time) {}

  // Accessor
  void set_estimated_time(unsigned short int estimated_time) {
    estimated_time_ = estimated_time;
  }

  // Mutator
  unsigned short int estimated_time() { return estimated_time_; }

  // This member function overrides Emergency's implementation
  void display() override {
    std::cout << "Emergency: " << description() << "\n";
    std::cout << "Location: " << location() << "\n";
    std::cout << "Estimated time: " << estimated_time_ << "\n";
    std::cout << "Report time: " << report_time() << "\n";
  }

  // This member function overrides Emergency's implementation
  std::string save_string() override {
    return "[PotentialEmergency]\n" + description() + "\n" + location() + "\n" +
           std::to_string(estimated_time_) + "\n" +
           std::to_string(report_time());
  }
};

// EmergencyManager class declaration
class EmergencyManager {
private: // Member variables
  Emergency* array_[100];
  int size_;

public:
  // Default constructor
  EmergencyManager() : size_(0) {}

  // Destructor
  ~EmergencyManager() {
    for (int i = 0; i < size(); i++) {
      delete array_[i];
      array_[i] = nullptr;
    }
  }

  // Accessor
  void set_size(int size) { size_ = size; }

  // Mutator
  int size() { return size_; }

  // The add Emergency member function prototype
  void add(Emergency* emergency);

  // The display_emergencies member function prototype
  void display_emergencies();

  // The show_priority_emergency member function prototype
  void show_priority_emergency(unsigned short int current_time);

  // The save_emergencies member function prototype
  void save_emergencies(const std::string& filename);

  // The load_emergencies member function prototype
  void load_emergencies(const std::string& filename);
};

// The display_menu function prototype
void display_menu();

// The create_emergency function prototype
Emergency* create_emergency();

// The create_multiple_emergency function prototype
MultipleEmergency* create_multiple_emergency();

// The create_potential_emergency function prototype
PotentialEmergency* create_potential_emergency();

// The get_current_time function prototype
unsigned short int get_current_time();

// The get_filename function prototype
std::string get_filename();
