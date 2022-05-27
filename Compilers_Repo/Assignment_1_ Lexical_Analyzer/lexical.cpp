#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

const string KEYS[10] = { "integer", "boolean", "if", "fi", "otherwise", "put", "get", "while", "true", "false" };
const char OPERATORS[7] = { '+', '<', '>', '/', '*', '-', '=' };
const char SEPARATORS[6] = { '[' , '{', '}', ';', '(', ')' };
enum STATES {
	ST_ERROR = -1,
	ST_START = 0,
	ST_IDENTIFIER_S, // single letter
	ST_IDENTIFIER_WU, // with underline
	ST_IDENTIFIER_WL, // with more letters
	ST_INTEGER,
};

// Function that says if an element is part of an array (both must be the same type)
template<class Type>
bool isInArray(const Type array[], int size, Type element) {
	for (int i = 0; i < size; i++) {
		if (element == array[i]) return true;
	}
	return false;
}

// Our Token Structure 
struct Token {
	string type; // For example: "integer"
	string lexeme; // For example: "123"
	// Constructors
	Token();
	Token(string tp, string lx) : type(tp), lexeme(lx) {}
};

// This is our FSM for integers and identifiers
void FSM(int &state, char k) {
	if (state == ST_START) {
		if (isalpha(k))
			state = ST_IDENTIFIER_S;
		else if (isdigit(k))
			state = ST_INTEGER;
		else
			state = ST_ERROR;
	}
	else if (state == ST_INTEGER and isdigit(k))
		state = ST_INTEGER;
	else if (state == ST_IDENTIFIER_S) {
		if (isalpha(k))
			state = ST_IDENTIFIER_WL;
		else if (k == '_')
			state = ST_IDENTIFIER_WU;
		else state = ST_ERROR;
	}
	else if (state == ST_IDENTIFIER_WL) {
		if (k == '_')
			state = ST_IDENTIFIER_WU;
		else if (!isalpha(k))
			state = ST_ERROR;
	}
	else if (state == ST_IDENTIFIER_WU) {
		if (isalpha(k))
			state = ST_IDENTIFIER_WL;
		else if (k != '_')
			state = ST_ERROR;
	}
	else
		state = ST_ERROR;
}

// Function just for traverse our tokens and save them into an output file
void saveResult(vector<Token> tokens) {
	// output file
	ofstream out("output.txt");
	// save every token in our vector
	out << "    TOKEN\t\tLEXEME" << endl;
	out << "---------------------------------------" << endl;
	for (int i = 0; i < tokens.size(); i++) {
		out << "    " << tokens[i].type << "\t\t" << tokens[i].lexeme << endl;
	}
	// close file
	out.close();
}

// Function to add a token to the list
void addToken(vector<Token> &tokens, string &lexeme, int &state) {
	// Validation for avoid to push empty strings when are consecutive spaces
	if (state == ST_START) return;
	// If token is an identifier (validate first if it is a keyword)
	if (state == ST_IDENTIFIER_S or state == ST_IDENTIFIER_WU or state == ST_IDENTIFIER_WL) {
		if (isInArray(KEYS, 10, lexeme)) tokens.push_back(Token("keyword", lexeme));
		// Validating maximum size
		else if (lexeme.length() <= 15)
			tokens.push_back(Token("identifier", lexeme));
		else
			cout << "Error: identifier '" << lexeme << "' too long (must be at most 15 characteres)" << endl;
	}
	// If token is an integer
	else if (state == ST_INTEGER) {
		// Validating maximum size
		if (lexeme.length() <= 10)
			tokens.push_back(Token("integer", lexeme));
		else
			cout << "Error: integer '" << lexeme << "' too long (must be at most 10 digits)" << endl;
	}
	else
		cout << "Error: Lexeme '" << lexeme << "' is not recognized." << endl;
	// Clean our variables
	lexeme = "";
	state = ST_START;
}

// Function that reads line by line and stores all tokens into a vector
vector<Token> analyze(string inputName) {
	ifstream in(inputName);
	// Just a open validation
	if (in.is_open()) {
		// Vars Definition
		string line, lexeme = "";
		bool isComment = false;
		vector<Token> tokens;
		int state = ST_START;
		// Process line by line
		while (getline(in, line)) {
			for (int i = 0; i < line.length(); i++) {
				// Closing comments when "*]" is found
				if (i < line.length() - 1 and line[i] == '*' and line[i + 1] == ']')
					isComment = false, i += 1;
				// Open comments when "[*" is found
				else if (i < line.length() - 1 and line[i] == '[' and line[i + 1] == '*')
					isComment = true, i += 1;
				// Process token just if is not inside a comment
				else if (!isComment) {
					// Separator $$
					if (i < line.length() - 1 and line[i] == '$' and line[i + 1] == '$') {
						addToken(tokens, lexeme, state); // finish the previous lexeme and add it
						tokens.push_back(Token("separator", "$$")), i += 1;
					}
					// Rest of separators
					else if (isInArray(OPERATORS, 7, line[i])) {
						addToken(tokens, lexeme, state); // finish the previous lexeme and add it
						tokens.push_back(Token("operator", string(1, line[i])));
					}
					// Operators
					else if (isInArray(SEPARATORS, 6, line[i])) {
						addToken(tokens, lexeme, state); // finish the previous lexeme and add it
						tokens.push_back(Token("separator", string(1, line[i])));
					}
					// When read an space, finish the current token read (and restart FSM)
					else if (isspace(line[i])) {
						addToken(tokens, lexeme, state);
					}
					else {
						lexeme += line[i];
						FSM(state, line[i]);
					}
				}
			}
		}
		// closing files
		in.close();
		// Returning the tokens
		return tokens;
	}
}

int main() {
	string inputName;
	cout << "Enter the name of the file to be analyzed: ";
	cin >> inputName;
	saveResult(analyze(inputName));

	return 0;
}

