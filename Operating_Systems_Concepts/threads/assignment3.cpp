/*
CPSC 351 Assignment 3:

Write a program that does the following (the links in the notes provide useful
information):


1.  The program shall be invoked as ./threads <number> where <number> is the
number of threads.  For example, ./threads 10 will create 10 threads.

2. The program will then create the specified number of threads and each thread
will then generate 100 random numbers in range of 0 -- 100000 and insert them into
the same shared binary search tree that is shared between all threads.

3.  All threads should be allowed to insert the numbers at the same time while
ensuring proper synchronization using pthread mutexes (i.e., no two threads will
be modifying the tree at the same time).

4. While the created threads are busy inserting numbers, the main thread waits
for the other threads to terminate.  Once all threads terminate the main thread
will print all numbers in the binary tree. Correctly printed numbers should be
in order (as that is the point of the binary search tree).

*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>

// The maximum thread number to be created
#define MAX_THREAD_NUMBER 1000

/* The size of the array where each thread stores 100 random numbers */
#define ARRAY_SIZE 100

// The mutex to protect the critical section
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

// Binary Search Tree Node Definition
struct Node
{
	// Holds the number to be inserted
  int key;
	// Pointer to the instance of left subtree node
  Node *left;
	// Pointer to the instance of right subtree node
  Node *right;

	/* Creates a node for the Binary Search Tree. Each node contains the number
	to be inserted,pointer to the left and right subtree */
  Node(int element)
	{
    key = element;
    left = nullptr;
    right = nullptr;
  }
};

class BST
{
private:
		// Parent node
    Node* root;
		/* The helper function to recursive BST insertion for BSTs with nodes
		containing the parent node and node to be inserted.*/
    void insertRecursive(Node*, Node*);
		/* The helper function to BST inorder traversal algorithm.*/
    void inorderRecursive(Node*);
		// The helper function to delete the nodes
		void clear(Node*);

public:
		// default constructor
    BST();
		/* Inserts a new node populated with key and value in a proper location
		obeying the BST ordering property (the value of the left subtree is less
		 than the value of the root and the value of the right subtree is
		 larger than root.)*/
    void insert(int);
		/* Prints the contents of the tree in ascending sorted order */
    void inorder();
		// Returns the tree to an empty state releasing all nodes
		void clear();
		// performs a deep node destruction
		~BST();

};

BST::BST()
{
		// Parent node initialized to nullptr
    root = nullptr;
}

// Instance of BST class to hold the shared binary search tree
BST tree;

// Insert a node
void BST::insert(int element)
{
		Node* node = new Node(element);
		// If the the tree is empty, the node to be inserted will be the root
		if (root == nullptr)
				root = node;
		else
				// If the the tree is not empty,
				// Calls the helper function for the recursive BST insertion
				insertRecursive(root, node);
}

// The recursive BST insertion containing parent node and node to be inserted
void BST::insertRecursive(Node* parent, Node* node)
{
		// If the node to be inserted is < the parent node, go to the left subtree
		if (node->key < parent->key)
		{
				// If the left node is empty,
				if (parent->left == nullptr)
						// Insert the node!
						parent->left = node;
				else
						// If the left node is not empty, go back up to search again
						insertRecursive(parent->left, node);
		}
		// If the node to be inserted is not < the parent node, go to the right subtree
		else
		{
					// If the right node is empty,
				if (parent->right == nullptr)
						// Insert the node!
						parent->right = node;
				else
						// If the right node is not empty, go back up to search again
						insertRecursive(parent->right, node);
		}
}

// Prints the numbers inorder
void BST::inorder()
{
    inorderRecursive(root);
}

// BST inorder traversal algorithm.
void BST::inorderRecursive(Node* node)
{
		// Base condition
    if (node == nullptr)
        return;
		// Traverse to the Left
    inorderRecursive(node->left);
		// Visit the node (root)
		fprintf(stderr, "%d\n", node->key);
		// Traverse to the Right
    inorderRecursive(node->right);
}

/**
 * Generated 100 random number for each thread and insert them into shared the BST
 * @param arg - the argument
 */
void* binaryThreadFunc(void* arg)
{
	/* The array of integers for each thread */
	int threadArray[ARRAY_SIZE];

  // Lock the mutex to prevent other threads from entering the critical section below
  if(pthread_mutex_lock(&myMutex) < 0)
  {
    perror("pthread_mutex_lock");
    exit(1);
  }

  /* Fill the each thread with random data */
  for(int index = 0; index < ARRAY_SIZE; ++index)
  {
    /* Generate a single random number between 0 and 100000
     * and save it in the array.
    */
    threadArray[index] = 	rand() % 100000;
		// Insert each number from the aray into the BST
		tree.insert(threadArray[index]);
  }

  // Unlock the mutex to allow other threads to enter the critical section
  if(pthread_mutex_unlock(&myMutex) < 0)
  {
    perror("pthread_mutex_unlock");
    exit(1);
  }

  return NULL;
}


BST::~BST()
{
	clear();
}

void BST::clear()
{
  clear(root);
  root = nullptr;
}


void BST::clear( Node* node )
{
  if( node == nullptr )
		return;

  clear( node->left);
  clear( node->right);

  delete node;
}


int main(int argc, char** argv)
{
	// Sanity check -- make sure the user provided all of the required arguments
	if(argc < 2)
	{
		fprintf(stderr, "USAGE: %s <NUMBER> \n", argv[0]);
		exit(1);
	}

  // store the thread number as a string first
  string strNumThreads = argv[1];

  // covert the the thread number from string to an int
  int numThreads = stoi(strNumThreads);

    // Check the thread size
  if(numThreads > MAX_THREAD_NUMBER)
  {
      fprintf(stderr, "Number too big. Maximum number = %d. Provided thread number = %d", MAX_THREAD_NUMBER, numThreads);
      exit(1);
  }

  // An array of numThreads ids
	pthread_t tids[numThreads];

  // Create number of threads
  for(int i = 0; i < numThreads; ++i)
  {
    // Create a thread that calls binaryThreadFunc()
    if(pthread_create(&tids[i], NULL, binaryThreadFunc, NULL) != 0)
    {
      perror("pthread_create");
      exit(1);
    }
  }

  /* Wait for all threads to finish */
  for(int i = 0; i < numThreads; ++i)
  {
    // Wait for the thread
    if(pthread_join(tids[i], NULL) != 0)
    {
      perror("pthread_join");
      exit(1);
    }
  }
	// Print all the numbers in order
	tree.inorder();

  return 0;
}
