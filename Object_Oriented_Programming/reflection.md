# Reflection

## Program description
TuffyAid Milestone 8:
This program updates previously created the TuffyAid Milestone class and functions by implementing another derived class a PotentialEmergency class that inherits from Emergency.

1) The new PotentialEmergency that inherits from Emergency will have a data member called estimated_time_ and keeps track of the potential time the emergency might happen. It will also have display() and save_string member functions that will override the ones from the base class.

2) The create_potential_emergency function will be created as a global function that provides all necessary values to create a PotentialEmergency object. It asks for the description, location, estimated time and report time. It will also return a pointer to a dynamically allocated PotentialEmergency object using the data from the user.

3) The load_emergencies function will be updated so that  it can read information on PotentialEmergencys. It will also create the corresponding object pointers that will be added to the Emergency pointer array.

4) Fianally, the menu will be updated so that it provides the option to create a potential emergency when the user presses O.

The rest of the functions will be work as expected.

## Test cases
// What tests will you conduct on your `PotentialEmergency` class to see if it was implemented correctly? Provide at least two tests.

### display_emergencies
#### Test case 1: Displaying a `PotentialEmergency` object
When the function is called, it displayed all the `PotentialEmergency` object information: description, location, estimated time, and report time.

### EmergencyManager class
#### Test case 1: `EmergencyManager`'s add member function
When the function is called, it stored all Emergency, MultipleEmergency and PotentialEmergency objects in the array correctly.

#### Test case 2: `EmergencyManager`'s load function
When this function is called, it was able to load the file and differentiate the type of the object as "[Emergency]" or "[MultipleEmergency]" or "[PotentialEmergency]" and stored the address of each object in the Emergency pointer array correctly. Tested with up to 4 combination of Emergency, MultipleEmergency and PotentialEmergency objects. Displayed all the Emergency object information as name, location, and report time, and for the MultipleEmergency object information as name,  other emergencies, location, and report time, and for the PotentialEmergency object information as name, location, estimated time and report timec orrectly.

## Issues encountered
### Open issues
No open issues.

### Resolved issues
No issues encountered.
