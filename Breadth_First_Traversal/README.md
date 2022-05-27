CPSC 131 Spring 2020
Introduction

Create a graph data structure using an adjacency list. The graph is undirected and unweighted. Then implement the Breadth First Search (BFS) Traversal on the graph. Use the Breadth First Search Traversal to find the shortest distance between the given source node and all other nodes in the graph.
Objective
You are given a header file, Graph.hpp, that defines what data member is in the Graph class. It also defines what functions you need to implement.

The main idea is to create a graph data structure using an adjacency list. And then implement two functionalities of Breadth First Traversal on the graph. 

Complete the implementation of this class, adding public/private member variables and functions as needed. Your code is tested in the provided main.cpp.

You are given one private data member to implement the graph data structure:

vector<vector<int>> adjacency_list

Using this is mandatory.

You are given the implementation of one function:
●	Graph() {} - default constructor

You will need to implement the following functions:
●	Graph(int) - one argument constructor to create adjacency_list of Graph with a given number of vertices
●	void addEdge(int, int) - add a new edge to the graph connecting vertex v1 to v2; Edge also needs to be added from v2 to v1
●	vector<int> BFS() - Implement Breadth First Search algorithm, using an STL queue. Using an STL queue is mandatory. For additional features, vectors may be used. The function returns the vertices that will be traversed in BFS order. These vertices are returned in a vector. Assume BFS begins at vertex 0.
●	vector<int> BFS_Shortest_Distance(int) - Find Shortest Distance from given source vertex to all vertices in the graph. Use BFS to find this shortest distance. Using an STL queue is mandatory. For additional features, vectors may be used. The function returns the shortest distance from the source vertex to each vertex in the graph. These shortest distances are returned in a vector.
●	void print_graph() - You can write this function to see if you have created a correct graph. This is optional. It can be helpful for debugging.
Source Code Files
You are given “starter” code files with declarations that may be incomplete and without any implementation. Implement the code and ensure that all the tests in main.cpp pass successfully.
●	Graph.hpp: This is to be completed
●	main.cpp: The main function tests the output of your functions. You may wish to add additional tests. During grading your main.cpp file will be replaced with the one you were provided with.
●	README.md: You must edit this file to include your name and CSUF email. Also include your project partner’s name and CSUF email, if you are working in a group. This information will be used so that we can enter your grades into Titanium.
