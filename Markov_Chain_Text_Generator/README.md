# CPSC 131 Spring 2020

I was tasked with working on an Artificial Intelligence program that can generate text. Your AI won’t be too complicated; it will train itself on text from a given text file. Hence the generated text will resemble (at least somewhat) text written by a human. The AI will form “Markov Chains” by storing associations between two words. When generating text, it will move from one word to the next randomly.

For example, given the following sentences:
	I like chess.
	I do not like rugby.

The Markov Chain generated could be expressed like:
	I do not like chess.
	I like rugby.

Objective:
TextGen.hpp header file defines what functions you need to implement. 
The main idea is to break sentences into words and store every word with its following word in a data structure. To generate a new sentence, you pick a word and then randomly pick one of its following word associations. 

Complete the implementation of this class, adding public/private member variables and functions as needed. Code is tested in the provided main.cpp.
You will need to implement the following functions:
●	TextGen(unsigned int seed) - The constructor; given an unsigned int seed value, you are to seed the random number generator with the command srand(seed). This ensures that the sentences you generate should match the ones we expect in the tests (as long as everything else works correctly).
●	bool isEndPunctuation(char) - This should return true if the given char is one of the following: . ? !
●	void read_in(const string &) 
●	vector<string> getValues(const string &) 
●	generateSentence() 
