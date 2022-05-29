# CPSC 535 Advanced Algorithms Spring 2021

Project 2: Cumulative frequencies 

In this project you will design and implement one algorithm related to strings. You will design the algorithm, 
describe the algorithm using clear pseudocode, and implement it using C/C++/C#/Java/Python, compile, test it, 
and submit BOTH the report (as a PDF file) and the files. The execution should take less than one hour for each
 input example. <p>

Calculating frequency of similar words
Given a text S of length n, one can easily calculate the frequency of each word in S using a linear time O(n) 
algorithm. But words can be similar, for example “foot” and “feet”, “day” and “days”,  “fear”and “scared”,
 “long” and “big”, “big” and “large”. So one can extract the cumulative frequency of similar words instead
 of individual words. This will be extremely useful for sentiment analysis of reviews (movies, products, 
services,etc.) and text summarization (blogs, text files, web articles, etc.), because it will output the 
essence of the entire text in a much smaller set of data. (This problem is similar but not the same as 
Exercise 17.7 “Baby Names” in “Cracking the Code Interview” book.)
Given two lists, one of words and their frequencies and the other of pairs of similar words, write an algorithm
 to print a new list of cumulative frequency of each set of similar words. Note that if “long” and “big” are similar,
 and “big” and “large” are similar, then “long” and “large” are similar. (It is both transitive and symmetric.) In the 
final list, any word can be used as representative of its set but for testing purposes, choosing the words that are
 the earliest in the alphabet is recommended.<p>
Example 1:<p>
Input: <p>
Words_Frequencies: WF[] = { (“foot”, 5), (“feet”, 12), (“day”, 3), (“days”, 8), (“fear”, 2), (“scared”, 1), (“long”, 12),
 (“large”, 5), (“big”,5), (“was”, 4), (“is”, 4), (“are”, 15)} of size 12
Synonyms: SYN[] = { (“foot”, “feet”), (“day”,“days”), (“fear”, “scared”), (“long” ,“big”), (“big” , “large”), (“is”, “are”),
 (“is”, “was”) } of size 7<p>
Output: CF[] = { (“feet”, 17), (“day”, 11), (“fear”,3), (“big”, 22), (“are”, 23) } of size 5
More examples will be added.<p>
Example 2:<p>
Input: <p>
Words_Frequencies: WF[] = { (“tons of”, 2), (“large number of ”, 12), (“mystical”, 13), (“magical”, 28), (“magic”, 5),
 (“unexplained”, 11), (“huge”, 2), (“large”, 51), (“horses”, 25), (“horse, 24), (“large mammal”, 24), (“herbivore”, 5)} 
of size 12<p>
Synonyms: SYN[] = { (“herbivore”, “horses”), (“horse”,“large mammal”), (“horses”, “large mammal”), (“large number of” ,“huge”),
 (“tons of” , “large”), (“huge”, “large”), (“mystical”, “magical”) , (“magical”,”unexplained”), (“magic”, “magical”)} of size 9
Output: CF[] = { (“herbivore”, 78), (“huge”, 67), (“magic”,57)} of size 3
Example 3:<p>
Words_Frequencies: WF[] = { (“tons of”, 2), (“large number of ”, 12), (“mystical”, 13), (“magical”, 28), (“magic”, 5), 
(“unexplained”, 11), (“huge”, 2), (“large”, 51), (“horses”, 25), (“horse, 24), (“large mammal”, 24), (“herbivore”, 5),
 (“large number of”,12)} of size 13<p>
Synonyms: SYN[] = { (“herbivore”, “horses”), (“horse”,“large mammal”), (“horses”, “large mammal”), (“large number of” ,“huge”),
 (“tons of” , “large”), (“huge”, “large”), (“mystical”, “magical”) , (“magical”,”unexplained”), (“magic”, “magical”),  
(“horse”,”large mammal”)} of size 10<p>
Output: CF[] = { (“herbivore”, 78), (“huge”, 67), (“magic”,57)} of size 3<p>

The variables WF[] and SYN[] must be read from the user, most preferred from a file. <p>
The output should display the resulting variable CF[]. Please check that your program executes correctly on the given examples.

