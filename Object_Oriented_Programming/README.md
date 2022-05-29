# CPSC 121 C++ Object Oriented Programming Fall 2019

## Potential Emergency
Create a new class called `PotentialEmergency` that inherits from `Emergency`. In addition to information stored by the `Emergency` class, it also keeps track of the potential time the emergency might happen. For example, the water level of a river close to town is really high and it can potentially lead to flooding in about 3 hours. This is going to be represented by a data member called `estimated_time_` (`unsigned short int`). A possible `PotentialEmergency` object might be a Flood, located at Tonto Basin, that might happen at 2000, that was reported at 1327.

Create accessors and mutators for the `estimated_time_` data member of `PotentialEmergency`.

Create a nondefault constructor that has the same parameters as the `Emergency` class constructor, but it provides an additional parameter for the estimated time.

Create a default constructor that sets its description to `"None"`, location to `"None"`, estimated time to `1000`, and report time to `800`.

Create a `display` member function that will override `Emergency`'s implementation. It works the same way except that it also displays the `estimated_time_` on the screen. For example, calling display on a `PotentialEmergency` object might show:

```
Emergency: Flood
Location: Tonto Basin
Estimated time: 2000
Report time: 1327
```

Create a `save_string` member function that will override `Emergency`'s implementation. It works the same way except that it uses a different name on the first line and provides the `estimated_time_`. For example, calling `save_string` on the same `PotentialEmergency` object above would return: `"[PotentialEmergency]\nFlood\nTonto Basin\n2000\n1327\n"`

### create_potential_emergency
Create a `create_potential_emergency` global function that asks the user to provide all necessary values to create a `PotentialEmergency` object. It asks for the description, location, estimated time, and report time. Here is an example of how it might ask input from the user.

<pre>
Please describe the emergency: <b>Flood</b>
Provide the location of the emergency:  <b>Tonto Basin</b>
Please provided the estimated time of the emergency: <b>2000</b>
Please enter the time that the emergency was reported: <b>1327</b>
</pre>

The function should also return a pointer to a dynamically allocated `PotentialEmergency` object using the values provided by the user.

### load_emergencies
Update your `load_emergencies` function so that it can read information on `PotentialEmergency`s. It should correctly create the corresponding object pointers that will be added to the `Emergency` pointer array.

### display_emergencies and show_priority_emergency
The other functionalities in `EmergencyManager` such as displaying, and showing priority emergencies should still work as expected.

## Menu
Update the menu to so it provides the option to create a *potential emergency* when the user presses **O**. This option should call the `create_potential_emergency` function and use the `EmergencyManager` object's `add` member function to add it into its `Emergency` pointer array.

## Other instructions
As usual, the code should be organized so that class and function prototypes are placed in a header file (`emergency.hpp`) while their implementations are placed in a source file (`emergency.cpp`).

Any member functions that contain over five lines of code or use any complex constructs should have their function prototypes in `emergency.hpp` and their corresponding implementation in `emergency.cpp`. Finally, the *main* method should be in the driver file (`tuffyaid.cpp`).

