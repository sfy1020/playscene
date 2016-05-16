/*-----------------------------------------------------------------------------------
File:			AStar.h
Author:			Steve Costa
Description:	The class performs an A* search for an arbitrary region.
-----------------------------------------------------------------------------------*/

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
using namespace std;

/*-----------------------------------------------------------------------------------
MACROS
-----------------------------------------------------------------------------------*/

// Get the index value for a single dimensional array given row, col and row width
#define GET_INDEX(row, col, NUM_COLS1) ((row) * (NUM_COLS1) + (col))

// Absolute macro
#ifndef ABS
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif

/*-----------------------------------------------------------------------------------
CONSTANTS
-----------------------------------------------------------------------------------*/

#define NO_LIST		0
#define	OPEN_LIST	1
#define CLOSE_LIST	2

/*-----------------------------------------------------------------------------------
This is the type definition of the nodes used in the search algorithm.
-----------------------------------------------------------------------------------*/

struct TAStarNode
{
	int g;			// Movement cost from starting location to this location
	int h;			// Movement cost estimate from this location to end destination

	int row;		// Row coordinate of matrix element node represents
	int col;		// Column coordinate of matrix element node represents

	int list_id;	// Identify which list the node belongs to

	TAStarNode* p_parent;		// Parent node
};

/*-----------------------------------------------------------------------------------
The A* algorithm will search through an array of TTerrainNode data types.  The
terrain_cost is the extra cost for navigating the particular terrain type.  This is
different from the g and h cost values automatically assigned to all cells.
The cost values stored in this array are >= 0.  In cases where some terrain
can be slower to navigate, a larger value can be assigned to it than other cells.
If a cell is not navigable at all, a negative value should be assigned to it.
For cases where all terrain values are the same a 0 value will suffice.
The a p_astar_node is used by the search algorithm to keep track of the cell's
corresponding TAStarNode used by the algorithm.
-----------------------------------------------------------------------------------*/

struct TTerrainNode
{
	int terrain_cost;
	TAStarNode* p_astar_node;

	// Constructors
	TTerrainNode() : terrain_cost(0), p_astar_node(nullptr) {}
	TTerrainNode(int cost) : terrain_cost(cost), p_astar_node(nullptr) {}
};

struct TPathNode
{
	int row;
	int col;
};

/*-----------------------------------------------------------------------------------
The actual AStar search class.
The open and close lists in the class are implemented as dynamic arrays of
pointers.  This makes it easy to dyanamically make the arrays large enogh to
contain any nodes, also each node is created once and the pointer is simply
passed between the arrays.
-----------------------------------------------------------------------------------*/

class CAStar
{
	// ATTRIBUTES
private:

	int num_ol_elements;		// Number of open elements
	TAStarNode** p_open_list;

	int num_cl_elements;		// Number of closed elements
	TAStarNode** p_close_list;

	int stdg;					// Standard g amount added as weight for each step

public:

	TPathNode* p_shortest_path;	// Path returned by the A* algorithm
	int shortest_path_length;	// Number of steps in the path

	// METHODS
private:

	int AllocateLists(int size);
	int ComposePath(TAStarNode* p_goal_node);
	void DeAllocateLists();

public:

	CAStar();

	int Init(int g);
	int FindPath(TTerrainNode* terrain, int NUM_ROWS1, int NUM_COLS1, int start_row,
		int start_col, int end_row, int end_col, TPathNode* &path_list, int &path_length);
	void Shutdown();

};

#endif