# TuffyAid Milestone 8

This is milestone 8 of the [TuffyAid Project](https://docs.google.com/document/d/1EnnXKjPqJ8is-26wZSQtQQw73b3VPEALkzfunsEkbVU/edit?usp=sharing).

# Requirements
In this milestone, we will implement another derived class called `PotentialEmergency` that will work with your `EmergencyManager`.


## PotentialEmergency
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

Please see the sample output below to guide the design of your program.

# Sample output
<pre>
Welcome to TuffyAid Emergency Response!

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>O</b>

Please describe the emergency: <b>Flood</b>
Provide the location of the emergency:  <b>Tonto Basin</b>
Please provided the estimated time of the emergency: <b>2000</b>
Please enter the time that the emergency was reported: <b>1327</b>

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>E</b>

Please describe the emergency: <b>Wildland Fire</b>
Provide the location of the emergency: <b>Beaumont</b>
Please enter the time that the emergency was reported: <b>922</b>

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>M</b>

Emergency: Camp Fire
Other emergencies: Missing person
Location: Butte County
Report time: 945

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>D</b>

Emergencies:

Emergency: Flood
Location: Tonto Basin
Estimated time: 2000
Report time: 1327

Emergency: Wildland Fire
Location: Beaumont
Report time: 922

Emergency: Camp Fire
Other emergencies: Missing person
Location: Butte County
Report time: 945

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>P</b>

Please enter the current time: <b>1035</b>
The earliest emergency was reported 1 hour(s) 13 minute(s) ago.

Emergency: Wildland Fire
Location: Beaumont
Report time: 922

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>S</b>

Please enter the filename: <b>emergencies.txt</b>
File saved!

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>L</b>

Please enter the filename: <b>new_e.txt</b>
File does not exist.

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>L</b>

Please enter the filename: <b>new_emergencies.txt</b>
File loaded!

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>D</b>

Emergencies:

Emergency: Ranch Fire
Location: Tehama
Report time: 904

What do you want to do?
E - Report an emergency
M - Report multiple emergencies
O - Report potential emergencies
D - Display emergencies
P - Show priority emergency
S - Save emergencies
L - Load emergencies
X - Exit
Action: <b>X</b>

Thank you for using TuffyAid Emergency Response!
</pre>

# Submission checklist
1. Created classes.
1. Created function prototypes.
1. Created function implementation.
1. Called functions in the driver accordingly.
1. Followed the [proper file structure for using functions](https://github.com/ILXL-guides/function-file-organization)
1. Compiled and ran the driver (`tuffyaid`).
1. Manually checked for compilation and logical errors.
1. Designed and tested your own test cases.
1. Ensured no errors on the unit test (`make test`).
1. Ensured no errors on the style check (`make stylecheck`).
1. Ensured no errors on the format check (`make formatcheck`).
1. Completed reflection file ([reflection.md](reflection.md))

# Code evaluation
Open the terminal and navigate to the folder that contains this exercise. Assuming you have pulled the code inside of `/home/student/ms01-tuffy` and you are currently in `/home/student` you can issue the following commands

```
cd ms01-tuffy
```

Use the `clang++` command to compile your code and the `./` command to run it. The sample code below shows how you would compile code save in `tuffyaid.cpp` and into the executable file `tuffyaid`. Make sure you use the correct filenames required in this problem.  Take note that if you make any changes to your code, you will need to compile it first before you see changes when running it.

```
clang++ -std=c++17 tuffyaid.cpp emergency.cpp -o tuffyaid
./tuffyaid
```

You can run one, two, or all the commands below to `test` your code, `stylecheck` your code's design, or `formatcheck` your work. Kindly make sure that you have compiled and executed your code before issuing any of the commands below to avoid errors.

```
make test
make stylecheck
make formatcheck
```

A faster way of running all these tests uses the `all` parameter.

```
make all
```

# Submission
1. When everything runs correctly,  let's copy your code into the Github repository. The first step is to add your code to what is called the staging area using git's `add` command. The parameter after `add` is the name of the file you want to add. There are cases when you have multiple changed files, so you can just type . (period) to add all modified files.

    ```
    git add tuffyaid.cpp emergency.cpp emergency.hpp
    ```
1. Once everything is in the staging area, we use the `commit` command to tell git that we have added everything we need into the staging area.

    ```
    git commit
    ```
1. In case it asks you  to configure global variables for an email and name, just copy the commands it provides then replace the dummy text with your email and Github username.

    ```
    git config --global user.email "tuffy@csu.fullerton.edu"
    git config --global user.name "Tuffy Titan"
    ```
    When you're done, make sure you type `git commit` again.    
1. Git will ask you to describe what you have added to the staging area. By default, you will use a command-line based editor called *nano*. Go ahead and provide a description then press <kbd>Ctrl</kbd> + <kbd>x</kbd> to exit. Press <kbd>Y</kbd> to confirm that you want to make changes and then press <kbd>Enter</kbd>.
1. Lets push all changes to the Github repository using git's `push` command. Provide your Github username and password when you are asked.

    ```
    git push
    ```
1. When you finish the exercise, go back to Titanium and click on the `Add submission` button in the lab exercise page. Provide a short message in the text area such as "finished lab exercise" and click on `Save changes`. Finally click on `Submit assignment` to inform your instructor that you are done.
