# A* Implementation in C

This program implements the A* algorithm to find the shortest path between two points in a two-dimensional grid. The grid can be of any size, but the program is set up to create a grid of size 50x25 by default. Walls can be added to the grid, and the algorithm will find the shortest path around them.

## Explanation of the A* algorithm

The A* algorithm is a pathfinding algorithm that is widely used in video games and robotics. It is a best-first search algorithm, meaning that it uses heuristics to determine which path to explore next. The algorithm starts at the starting point and examines all adjacent nodes to determine the best path to take. It uses a heuristic function to estimate the distance from each adjacent node to the target node. The algorithm then chooses the node with the lowest estimated cost and continues the search until the target node is found.

The program works by first initializing the grid and adding walls randomly. The starting and ending points are also set randomly, although they are guaranteed to be on opposite corners of the grid. The algorithm then calculates the heuristics for each node and initializes the open and closed sets.

The open set contains all nodes that have been examined but have not yet been explored. The closed set contains all nodes that have been examined and explored. The algorithm then selects the starting node and adds it to the open set. The algorithm then loops until the target node is found or the open set is empty.

At each iteration of the loop, the algorithm examines the node with the lowest cost in the open set. It then examines all adjacent nodes to determine if they should be added to the open set. The adjacent nodes are added to the open set if they have not already been examined and if they are not walls. The algorithm then calculates the cost of each adjacent node and sets the parent of the adjacent node to the current node. If the target node is found, the algorithm reconstructs the path and prints it to the console.

## Usage

To run the program, navigate to the directory containing main.c and compile the program using the following command:

```gcc main.c -o astar```

Once the program is compiled, it can be run using the following command:

```./astar```

The program will then run and output the shortest path to the console. The program can be customized by changing the values of the constants at the top of the file.
