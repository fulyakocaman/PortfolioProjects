# CPSC 481-01 Summer 2021 Project 1
Pacman StateSpaceSearch

Group Member:
Fulya Kocaman fulyakocaman@csu.fullerton.edu

Project 1 – State Space Search for Pacman

In this project, your Pacman agent will find paths through his maze world, both to reach a 
particular location and to collect food efficiently. You will build general search algorithms and 
apply them to Pacman scenarios.
this project includes an autograder for you to grade your answers on your machine. This can be 
run with the command:
python autograder.py
The code for this project consists of several Python files, some of which you will need to read 
and understand in order to complete the assignment, and some of which you can ignore. You 
can download all the code and supporting files as a zip archive (written in Python 3.6).

Files you'll edit:
search.py Where all of your search algorithms will reside.

Files you might want to look at:
pacman.py The main file that runs Pacman games. This file describes a Pacman Game State 
type, which you use in this project.
game.py The logic behind how the Pacman world works. This file describes several 
supporting types like Agent State, Agent, Direction, and Grid.
util.py Useful data structures for implementing search algorithms.
searchAgents.py A variety of different types of Pacman agents.
test_cases/ Directory containing the test cases for each question

Supporting files you can ignore:
graphicsDisplay.py Graphics for Pacman
graphicsUtils.py Support for Pacman graphics
textDisplay.py ASCII graphics for Pacman
ghostAgents.py Agents to control ghosts
keyboardAgents.py Keyboard interfaces to control Pacman
layout.py Code for reading layout files and storing their contents
autograder.py Project autograder
testParser.py Parses autograder test and solution files
testClasses.py General autograding test classes
searchTestClasses.py Project 1 specific autograding test classes