#include <iostream>
#include <vector>
#include <string>
#include "Graph.hpp"
using namespace std;

// Global static variables
static int testCount = 0;
static const int testTotal = 5;
static const string GREEN = "\033[32m";
static const string RED = "\033[31m";
static const string RESET = "\033[0m";

vector<int> v1;
vector<int> v2;


template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual);

// Main
int main(int argc, char const *argv[]) 
{
	//BFS Test 1
	{
		Graph G(9);//9 vertices
		G.addEdge(0, 1);
		G.addEdge(0, 3);
		G.addEdge(0, 8);
		G.addEdge(1, 7);
		G.addEdge(2, 3);
		G.addEdge(2, 5);
		G.addEdge(2, 7);
		G.addEdge(3, 4);
		G.addEdge(4, 8);
		G.addEdge(5, 6);
		
		//G.print_graph();

		v1 = { 0, 1, 3, 8, 7, 2, 4, 5, 6 };

		v2 = G.BFS();

		assertVectorEquals("Breadth First Test", v1, G.BFS());
		v1.clear();
		v2.clear();
	}

	
	//BFS Test 2 
	{
		Graph G(9);//9 vertices
		G.addEdge(0, 1);
		G.addEdge(0, 8);
		G.addEdge(2, 3);
		G.addEdge(2, 4);
		G.addEdge(2, 5);
		G.addEdge(2, 8);
		G.addEdge(4, 7);
		G.addEdge(5, 6);
		G.addEdge(6, 7);
		G.addEdge(6, 8);
		
		//G.print_graph();

		
		v1 = { 0, 1, 8, 2, 6, 3, 4, 5, 7 };

		v2 = G.BFS();

		assertVectorEquals("Breadth First Test", v1, G.BFS());

		v1.clear();
		v2.clear();

	}

	//BFS Test 3 
	{
		Graph G(5);//5 vertices
		G.addEdge(0, 1);
		G.addEdge(0, 4);
		G.addEdge(1, 2);
		G.addEdge(1, 3);
		G.addEdge(2, 3);
		G.addEdge(3, 4);
		
		//G.print_graph();


		v1 = { 0, 1, 4, 2, 3 };

		v2 = G.BFS();

		assertVectorEquals("Breadth First Test", v1, G.BFS());

		v1.clear();
		v2.clear();

	}
	//BFS Shortest Distance Test 1
	{
		Graph G(8);//8 vertices

		
		G.addEdge(0, 1);
		G.addEdge(0, 3);
		G.addEdge(1, 2);
		G.addEdge(3, 4);
		G.addEdge(3, 7);
		G.addEdge(4, 5);
		G.addEdge(4, 6);
		G.addEdge(4, 7);
		G.addEdge(5, 6);
		G.addEdge(6, 7);

		//G.print_graph();


		v1 = { 0, 1, 2, 1, 2, 3, 3, 2 };

		v2 = G.BFS_Shortest_Distance(0);

		

		assertVectorEquals("Shortest Distance Test", v1, G.BFS_Shortest_Distance(0));
		

		
		v1.clear();
		v2.clear();
		
	}

	//BFS Shortest Distance Test 2
	{
		Graph G(8);//8 vertices


		G.addEdge(0, 1);
		G.addEdge(0, 3);
		G.addEdge(1, 2);
		G.addEdge(3, 4);
		G.addEdge(3, 7);
		G.addEdge(4, 5);
		G.addEdge(4, 6);
		G.addEdge(4, 7);
		G.addEdge(5, 6);
		G.addEdge(6, 7);

		//G.print_graph();


		
		v1 = { 1, 2, 3, 0, 1, 2, 2, 1 };

		v2 = G.BFS_Shortest_Distance(3);

		assertVectorEquals("Shortest Distance Test", v1, G.BFS_Shortest_Distance(3));

		v1.clear();
		v2.clear();
		
	}
	cout << "TESTS PASSED: " << testCount << "/" << testTotal << 
		"\t(" << (100* float(testCount)/float(testTotal)) << "%)"  << endl;

	cin.get();
	return 0;
}

// Helper Functions
template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& expected, const vector<U>& actual) {
	if (expected.size() == actual.size()) {
		for (size_t i = 0; i < expected.size(); i++) {
			if (expected[i] != actual[i]) {
				// Red colored text
				cout << RED << "FAILED "
					<< RESET << nameOfTest << ": expected '" << expected[i] << "' but actually '" << actual[i] << "'" << endl;
				return false;
			}
		}

		// Green colored text
		cout << GREEN << "PASSED "
			<< RESET << nameOfTest << ": expected and actual lists match: {";
		for (int i = 0; i < expected.size(); i++) {
			cout << " " << expected[i];
		}
		cout << " }" << endl;

		testCount++;
		return true;
	}

	// Red colored text
	cout << RED << "FAILED "
		<< RESET << nameOfTest << ": expected size '" << expected.size() << "' but actually size is '" << actual.size() << "'" << endl;
	return false;
}

