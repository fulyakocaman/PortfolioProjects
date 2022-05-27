
#pragma once
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {

private:
  vector<vector<int>> adjacency_list; // mandatory

public:
  Graph() {} // default constructor

  Graph(int); // one argument constructor, creates adjacency_list of Graph with
              // a given number of vertices

  void addEdge(int, int); // add a new edge from vertex v1 to v2
                          // edge also needs to be added from v2 to v1

  vector<int> BFS();
  // Implement Breadth First Search algorithm, using an STL queue
  // Using an STL queue is mandatory. The function returns the vertices that
  // will be traversed in BFS order.

  vector<int> BFS_Shortest_Distance(int);
  // Find Shortest Distance from src vertex
  // Using an STL queue is mandatory. The function returns the shortest distance
  // from the source vertex to each vertex in the graph

  void print_graph(); // optional, for debugging
};

Graph::Graph(int vertices) {
   adjacency_list.resize(vertices); // allocating memory for the adjacency_list
 }

void Graph::addEdge(int v1, int v2) {

  adjacency_list[v1].push_back(v2); // adding a new edge from vertex v1 to v2
  adjacency_list[v2].push_back(v1); // adding a new edge from vertex v2 to v1
}

vector<int> Graph::BFS() {
  vector<int> bfs_trav;

  // initiliaze all of them to false, not visited yet
  bool visited[adjacency_list.size()];
  for (int i = 0; i < adjacency_list.size(); i++) {
    visited[i] = false;
  }

  queue<int> que;

  que.push(0); // pushing starting vector as 0

  visited[0] = true; // marking 0 as visited

  while (!que.empty()) {
    int value = que.front(); // setting the front element to the variable value

    que.pop(); // popping the value from the queue
    bfs_trav.push_back(value); // pushing the value to the vector

    // Looking for adjacent vertex to the value
    for (auto i : adjacency_list[value]) {
      if (!visited[i]) {
        que.push(i);       // pushing the adjacent vertex(s) to the queue
        visited[i] = true; // marking the vertex(s) as visited
      }
    }
  }

  return bfs_trav;
}

vector<int> Graph::BFS_Shortest_Distance(int start) {

  vector<int> distance;
  distance.resize(adjacency_list.size()); // allocating memory for the vector

  // initiliaze all of them to false, not visited yet
  bool visited[adjacency_list.size()];
  for (int i = 0; i < adjacency_list.size(); i++) {
    visited[i] = false;
  }

  queue<int> que;

  que.push(start);       // pushing starting int to the queue

  visited[start] = true; // marking the starting as visited

  distance[start] = 0;   // setting starting distance vector as 0

  while (!que.empty()) {
    int value = que.front(); // setting the front element to the variable value
    que.pop();               // popping the value from the queue

    // Looking for adjacent vertex to the value
    for (auto i : adjacency_list[value]) {
      if (!visited[i]) {
        distance[i] = distance[value] + 1;
        que.push(i);       // pushing the adjacent vertex(s) to the queue
        visited[i] = true; // marking the vertex(s) as visited
      }
    }
  }

  return distance;
}

void Graph::print_graph() {
  for (int i = 0; i < adjacency_list.size(); i++) {
    // print current vertex number
    cout << i << " --> ";

    // print all neighboring vertices of vertex i
     for (auto i: adjacency_list[i]) {
      cout << i << " ";
    }
    cout << endl;
  }
}
