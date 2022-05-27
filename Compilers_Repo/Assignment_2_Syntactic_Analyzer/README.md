Assignment 2 Syntactic Analyzer
 
Problem Statement: The problem is to determine whether the given source code is syntactically correct or not. 
We solve this using a top-down parser for syntactic analysis. If the source code’s syntax is correct, the parse 
trace will be outputed to a file. If there is an error, the details of the first error encountered will be 
printed to the output file.

How to execute the program: 

Windows (Visual Studio)
1.	RUN compiler.cpp in VS or compiler.exe
2.	Enter the .txt file name if it’s in the current directory, or the relative path if it’s not.

Linux
1.	Within command prompt, open ‘compiler’ directory.
2.	Compile it with the command “g++ compiler.cpp -o compiler”.
3.	Run it with “./compiler”
4.	When the program runs it will prompt you to enter the source file name’s relative path (ex. ../test.txt).
