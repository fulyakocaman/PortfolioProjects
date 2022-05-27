# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    
    # Using the Stack (LIFO) data structure from util.py for open 
    open = util.Stack()
    
    # Intialize the data structure open with the start state using the push function
    # Push the start state and list of the information necessary to reconstruct the path
    # For the start state the information will be an empty list
    open.push((problem.getStartState(), []))

    # Initialize the closed data structure to an empty list
    closed = []

    # While open is not empty
    while not open.isEmpty():
         
        # (state, info) pairs from the stack, where state = current state, info = a list of actions
        # Remove the leftmost state from open and call it X
        state, info = open.pop()
        X = state

        # If state is the goal state (if the goal is found), return the list of actions
        if problem.isGoalState(X):
            return info
        else:
            # Check to see if X is not in closed
            if X not in closed:
                # Generate children of X since X is not the goal state
                children = problem.getSuccessors(X)
                # Place X on closed
                closed.append(X)
                # Children is a list of triples (nextState, action, stepCost)
                # nextState = successor to the current state
                # action = the action required to get there
                # stepCost = incremental cost of expanding to that successor
                for nextState, action, stepCost in children:
                    # Loop check to discard the children of state if already on open
                    # Compare children = (nextState, action) pairs with open's (state, info) pairs
                    # Push children that are not in open to the open data structure 
                    if (nextState, action) not in (state, info):
                        # Put the remaing children on the left end of open 
                        # Using a stack data structure for open will achieve that
                        # The list of actions for the nextState will contain its own actions
                        # plus the information of the previous       
                        open.push((nextState, info + [action]))

    util.raiseNotDefined()


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"

    # Using the Queue(FIFO) data structure from util.py for open 
    open = util.Queue()
    
    # Intialize the data structure open with the start state using the push function
    # Push the start state and list of the information necessary to reconstruct the path
    # For the start state the information will be an empty list
    open.push((problem.getStartState(), []))

    # Initialize the closed data structure to an empty list
    closed = []

    # While open is not empty
    while not open.isEmpty():
         
        # (state, info) pairs from the queue, where state = current state, info = a list of actions
        # Remove the leftmost state from open and call it X
        state, info = open.pop()
        X = state

        # If state is the goal state (if the goal is found), return the list of actions
        if problem.isGoalState(X):
            return info
        else:
            # Check to see if X is not in closed
            if X not in closed:
                # Generate children of X since X is not the goal state
                children = problem.getSuccessors(X)
                # Place X on closed
                closed.append(X)
                # Children is a list of triples (nextState, action, stepCost)
                # nextState = successor to the current state
                # action = the action required to get there
                # stepCost = incremental cost of expanding to that successor
                for nextState, action, stepCost in children:
                    # Loop check to discard the children of state if already on open
                    # Compare children = (nextState, action) pairs with open's (state, info) pairs
                    # Push children that are not in open to the open data structure  
                    if (nextState, action) not in (state, info):
                        # Put the remaing children on the right end of open 
                        # Using a queue data structure for open will achieve that
                        # The list of actions for the nextState will contain its own actions 
                        # plus the information of the previous       
                        open.push((nextState, info + [action]))
                    
    util.raiseNotDefined()
  

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"

    # Using the PriorityQueue data structure from util.py for open
    # This data structure allows in quick retrieval of the lowest-priority item in the queue
    open = util.PriorityQueue()

    # Intialize the data structure open with the start state using the push function
    # We are pushing item = (state, info) pairs AND priority to the priority queue,
    # where state = current state, info = a list of actions 
    # and priority = priority associated with the item intialized to 0.
    #open.push((problem.getStartState(),shortestPath),0)
    open.push((problem.getStartState(), []), 0);

    # Initialize the closed data structure to an empty list
    closed = []

    while not open.isEmpty():

        # Remove the leftmost state from open and call it X
        state, shortestPath = open.pop()
        X = state

        # If state is the goal state (if the goal is found), return the shortest path
        if problem.isGoalState(X):
            return shortestPath
        else:
            # Check to see if X is not in closed
            if X not in closed:
                # Generate children of X since X is not the goal state
                children = problem.getSuccessors(X)
                # Children is a list of triples (nextState, action, stepCost)
                # nextState = successor to the current state
                # action = the action required to get there
                # stepCost = incremental cost of expanding to that successor
                for nextState, action, stepCost in children:
                    # Loop check to discard the children of state if already on open or closed
                    # Compare children = (nextState, action) pairs with open's (state, shortestPath) pairs
                    # Push children that are not in open nor closed to the open data structure
                    if ((nextState, action) not in (state, shortestPath)) or (nextState not in closed):
                        # the cost function f(n) = cost(n) + h(n)
                        # cost(n) = the total cost of actions from n to the start state which contains the 
                        # total cost of its own actions and the information of the previous
                        # getCostOfActions will be called to get the total cost of actions from the start state
                        # h(n) = admissible heuristic estimate of the cost from n to goal state and never overestimates 
                        costFunc = problem.getCostOfActions(shortestPath + [action]) + heuristic(nextState, problem) 
                        # Reorders the queue by the lowest cost
                        open.update((nextState, shortestPath + [action]), costFunc)
                    elif ((nextState, action) in (state, shortestPath)):
                        # if the child was reached by a shorter path, give the state on open shorter path
                        if(len(action) < len(shortestPath)): 
                            # Reorders the queue by the lowest cost
                            open.update((nextState, [action]), costFunc)
                    elif(nextState in closed):
                        # if the child was reached by a shorter path, give the state on open shorter path
                        if(len(action) < len(shortestPath)):
                            # Remove the state from closed and add the child to open
                            action = closed.pop()
                            # Reorders the queue by the lowest cost
                            open.update((nextState, [action]), costFunc)                                            
        # Place X on closed
        closed.append(X) 
  
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
