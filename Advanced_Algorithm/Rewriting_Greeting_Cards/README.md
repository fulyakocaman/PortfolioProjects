CPSC 535 Advanced Algorithms
Project 1: Rewriting greeting cards
Prof. Doina Bein, CSU Fullerton
dbein@fullerton.edu

Introduction: In this project you will design and implement one algorithm related to strings. You will design 
the algorithm, describe the algorithm using clear pseudocode, and implement it using C/C++/C#/Java/Python, 
compile, test it, and submit BOTH the report (as a PDF file) and the files. The execution should take less than one hour.

Rewriting greeting ecards
People appreciate small gestures like receiving a greeting card on special occasions, even if it is delivered electronically. Sometimes writing this greeting takes longer than planned because it is not easy to come up with something thoughtful. But once you do itl, why not reusing most of the text for another occasion? For example, a congratulation email on a new car may be similar to a congratulation email on a  new house. One can copy and paste parts of the previous greeting to make it into a new greeting, but we would like to develop software that does it for us. The problem can be formulated as follows: Given a string S of length N>0, and a list of M pairs of strings LS, each pair representing a string to be replaced and the second being the actual replacement, display the new string R that is obtained by replacing every occurrence of the first string in each pair with the corresponding second string in the pair. The string matching must be case sensitive.
Example 1:
Input:
S[] = “My dear Anna, let me congratulate you on the beautiful car that you purchased today. It looks very posh. I hope you got a good deal. Cars are expensive but much needed. Best regards, Naomi.”
N = 147
M = 4
LS[] = { {“Anna”, “Jovi and Victor”} , { “car”, “house”}, {“today”, “last week”}, {“posh”, “well built”}}
Output:
R[] = “My dear Jovi and Victor, let me congratulate you on the beautiful house that you purchased last week. It looks very well built. I hope you got a good deal. Cars are expensive but much needed. Best regards, Naomi.”
Example 2:
Input:
S[] = “Our newest students have been asked to stay today until the end of the classes. The old principal.”
N = 95
M = 5
LS[] = { {“new”, “old”} , { “student”, “teacher”}, {“to”, “yester”}, {“old”, “young”}, {“end”, “beginning”}}
Output:
R[] = “Our oldest teachers have been asked yester stay yesterday until the beginning of the classes. The young principal.”
Example 3:
Input:
S[] = “Our newest students have been asked to stay today until the end of the classes. The old principal.”
N = 95
M = 5
LS[] = {{"old", "young"},  {"student", "teacher"},  {"to", "yester"},  {"end", "beginning"}, {"new", "old"}}
Output:
R[] = “Our oldest teachers have been asked yester stay yesterday until the beginning of the classes. The young principal.”
Variables N and M can be computed from S[] and LS{} so it is up to you if you want the user to input them or not. The variables S[] and LS[] must be read from the user, most preferred from a file. 
The output should display the resulting string R. Please check that your program executes correctly on the two given examples. Please create more examples on your own and test them..
s