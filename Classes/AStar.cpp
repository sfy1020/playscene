/*-----------------------------------------------------------------------------------
File:			AStar.cpp
Author:			Steve Costa
Description:	The class performs an A* search for an arbitrary region.
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
Include files
-----------------------------------------------------------------------------------*/

#include "AStar.h"
//#include <stdio.h>
#include <tchar.h>

/*-----------------------------------------------------------------------------------
Constructor
-----------------------------------------------------------------------------------*/

CAStar::CAStar()
{
	p_open_list = nullptr;
	p_close_list = nullptr;
	p_shortest_path = nullptr;
}

/*-----------------------------------------------------------------------------------
Initialise with the global cost for traversing a single tile (g must be positive).
return -1 on failure, 1 on success
-----------------------------------------------------------------------------------*/

int CAStar::Init(int g)
{
	if (g < 0) return -1;
	else stdg = g;

	return 1;
}

/*-----------------------------------------------------------------------------------
Allocate arrays of pointers as large as the number of cells in the search terrain.
Do this before a search.
-----------------------------------------------------------------------------------*/

int CAStar::AllocateLists(int size)
{
	// Allocate Open List
	if ((p_open_list = (TAStarNode**)calloc(size, sizeof(TAStarNode*))) == nullptr) {
		free(p_open_list);
		p_open_list = nullptr;
		return -1;		// Failed to allocate array
	}

	// Allocate Close List
	if ((p_close_list = (TAStarNode**)calloc(size, sizeof(TAStarNode*))) == nullptr) {
		free(p_close_list);
		p_close_list = nullptr;
		return -1;
	}

	return 1;
}

/*-----------------------------------------------------------------------------------
Clean up after a search.
-----------------------------------------------------------------------------------*/

void CAStar::DeAllocateLists()
{
	// All the dynamically allocated nodes are referencible from either
	// the open_list or the close_list, clear the allocated memory using
	// the pointers stored in the array elements.

	for (int i = 0; i < num_ol_elements; i++)
	{
		free(p_open_list[i]);
		p_open_list[i] = nullptr;
	}
	free(p_open_list);
	p_open_list = nullptr;

	for (int i = 0; i < num_cl_elements; i++)
	{
		free(p_close_list[i]);
		p_close_list[i] = nullptr;
	}
	free(p_close_list);
	p_close_list = nullptr;
}

/*-----------------------------------------------------------------------------------
This is the procedure used by the qsort algorithm for sorting the array of pointers.
It is encapsulated in a unnamed name space to prevent global scope.
-----------------------------------------------------------------------------------*/

namespace {
	int CompFunc(const void *arg1, const void *arg2)
	{
		const TAStarNode* c1 = *(TAStarNode**)arg1;
		const TAStarNode* c2 = *(TAStarNode**)arg2;

		if ((c1->g + c1->h) < (c2->g + c2->h)) return -1;
		else if ((c1->g + c1->h) == (c2->g + c2->h)) return 0;
		else return 1;
	}
}

/*-----------------------------------------------------------------------------------
This is the main method which will search an array for the shortest navigable
path from the start cell to the end cell.

terrain =	Pointer to first element in the array of the terrain elements.
numRows =	The number of rows in the terrain array.
numCols =	The number of columns in the terrain array.
startRow =	The row the search is starting from.
startCol =	The column the search is starting from.
endRow =	The destination row.
endCol =	The destination column.
pathList =	The method accepts a reference to a pointer which gets assigned
to the array of the steps required to reach the goal.
pathLength = The number of elements in the list being returned.

If the method is successful it will return 1.
-1 for memory allocation problems.
-2 for path not found
-----------------------------------------------------------------------------------*/

int CAStar::FindPath(TTerrainNode* terrain, int NUM_ROWS1, int NUM_COLS1, int start_row,
	int start_col, int end_row, int end_col, TPathNode* &path_list, int& path_length)
{
	int id1, id2;
	int new_g;
	int current_row, current_col;
	bool sol_found = false;
	TAStarNode* p_parent = nullptr;
	TAStarNode* p_child = nullptr;
	num_ol_elements = 0;
	num_cl_elements = 0;
	int manhattan_h;

	// Allocate memory for the "open" and "close" lists
	if (AllocateLists(NUM_ROWS1 * NUM_COLS1) < 0) {
		cout << "Failed to allocate array" << endl;
		return -1;
	}

	for (;;) {
		// Allocate memory for one element
		if ((p_parent = (TAStarNode*)calloc(1, sizeof(TAStarNode))) == nullptr) {
			// Return the array passed to the method to initial state
			for (int i = 0; i < NUM_ROWS1 * NUM_COLS1; i++)
				terrain[i].p_astar_node = nullptr;
			DeAllocateLists();
			free(p_parent);
			p_parent = nullptr;
			cout << "Failed to allocate node" << endl;
			return -1;
		}

		// Choose node from the "open" list with the smallest f weight
		// we must sort the list first so that the smallest is the first in the array
		if (num_ol_elements > 0) {
			qsort((void*)p_open_list, size_t(num_ol_elements), sizeof(TAStarNode*), CompFunc);
			p_parent = p_open_list[0];
		}
		// If the list is empty either we are at the beginning or there is no solution
		else {
			id1 = GET_INDEX(start_row, start_col, NUM_COLS1);

			if (terrain[id1].p_astar_node == nullptr) {  // It is not in a list
				p_parent->col = start_col;
				p_parent->row = start_row;
				p_parent->g = 0;
				manhattan_h = (ABS(start_col - end_col) + ABS(start_row - end_row)) * 10;
				p_parent->h = manhattan_h;
				p_parent->p_parent = nullptr;
				p_parent->list_id = OPEN_LIST;

				// Add the node to the "open" list
				p_open_list[num_ol_elements++] = p_parent;
				terrain[GET_INDEX(start_row, start_col, NUM_COLS1)].p_astar_node = p_parent;
			}
			else {	// This node has already been added, therefore no solution
				// Return the array passed to the method to initial state
				for (int i = 0; i < NUM_ROWS1 * NUM_COLS1; i++)
					terrain[i].p_astar_node = nullptr;
				DeAllocateLists();
				return -2;
			}
		}

		//----------------------------------------------------------------------
		// Look at each adjacent, reachable square and add it to the "open" list
		// while saving which parent it belongs to
		// ***	In this implementation squares that are diagonal from the 
		//		being considered are not legal.
		// Check the four adjacent cells (not checking diagonal cells)
		// Get index of cell moving from (we do this to compter the cell heights
		// of the cell moving from to the cell moving to to make sure it the
		// difference is not to high for the golem to get to
		//-----------------------------------------------------------------------
		id1 = GET_INDEX(p_parent->row, p_parent->col, NUM_COLS1);

		for (int i = 0; i < 4; i++)
		{
			if (i == 0) {
				current_row = p_parent->row - 1;
				current_col = p_parent->col;
			}
			else if (i == 1) {
				current_row = p_parent->row + 1;
				current_col = p_parent->col;
			}
			else if (i == 2) {
				current_row = p_parent->row;
				current_col = p_parent->col - 1;
			}
			else if (i == 3) {
				current_row = p_parent->row;
				current_col = p_parent->col + 1;
			}

			if (current_row >= 0 && current_row < NUM_ROWS1 && current_col >= 0 && current_col < NUM_COLS1) {

				id2 = GET_INDEX(current_row, current_col, NUM_COLS1);		// Get index of cell moving to

				// Make sure terrain can be navigated on
				if (terrain[id2].terrain_cost >= 0) {

					// If it is not already part of the open or close lists
					if (terrain[id2].p_astar_node == nullptr) {

						// Allocate memory for one element
						if ((p_child = (TAStarNode*)calloc(1, sizeof(TAStarNode))) == nullptr) {
							// Return the array passed to the method to initial state
							for (int i = 0; i < NUM_ROWS1 * NUM_COLS1; i++)
								terrain[i].p_astar_node = nullptr;
							DeAllocateLists();
							free(p_child);
							p_child = nullptr;
							cout << "Failed to allocate node" << endl;
							return -1;
						}

						p_child->col = current_col;
						p_child->row = current_row;
						p_child->p_parent = p_parent;
						p_child->g = p_parent->g + stdg + terrain[id2].terrain_cost;

						// Use Manhattan method to calculate h
						manhattan_h = (ABS(current_col - end_col) + ABS(current_row - end_row)) * 10;
						p_child->h = manhattan_h;

						// Add this node to the "open" list
						p_open_list[num_ol_elements++] = p_child;
						terrain[id2].p_astar_node = p_child;

						// Check to see if the node we just added was the final destination node
						if (current_row == end_row && current_col == end_col) {
							sol_found = true;
							break;
						}
					}
					// It is on the open list
					else if (terrain[id2].p_astar_node->list_id == OPEN_LIST) {
						new_g = p_parent->g + stdg;
						if (new_g < terrain[id2].p_astar_node->g) {	// This route is faster
							terrain[id2].p_astar_node->g = new_g;
							terrain[id2].p_astar_node->p_parent = p_parent;
						}
					}

				} // End if terrain_cost >= 0
			} // End if current row, col is legal
		} // End for

		// Solution was found, compose the path list and exit
		if (sol_found) {
			if (ComposePath(p_child) < 0) return -1;
			break;
		}

		// We have checked all the adjacent cells on the terrain, we can now
		// put this node into the "closed" list
		p_close_list[num_cl_elements++] = p_open_list[0];	// First element in open go to closed
		p_open_list[0] = p_open_list[--num_ol_elements];	// Last element in open go to first
		p_open_list[num_ol_elements] = nullptr;

	}

	path_list = p_shortest_path;
	path_length = shortest_path_length;

	// Return the array passed to the method to initial state
	for (int i = 0; i < NUM_ROWS1 * NUM_COLS1; i++)
		terrain[i].p_astar_node = nullptr;

	DeAllocateLists();				// Clear allocated data

	return 1;
}

/*-----------------------------------------------------------------------------------
Order the path to the goal once the A* is complete
-----------------------------------------------------------------------------------*/

int CAStar::ComposePath(TAStarNode* p_goal_node)
{
	TAStarNode* p_temp;
	shortest_path_length = 1;

	// Loop through the path to find out its length
	for (p_temp = p_goal_node; p_temp->p_parent != nullptr; p_temp = p_temp->p_parent, shortest_path_length++);

	// Allocate enough memory for the length of the path
	if (p_shortest_path != nullptr) {
		free(p_shortest_path);
		p_shortest_path = nullptr;
	}
	if ((p_shortest_path = (TPathNode*)calloc(shortest_path_length, sizeof(TPathNode))) == nullptr) {
		free(p_shortest_path);
		p_shortest_path = nullptr;
		return -1;
	}

	// Assign the nodes to each element
	for (int i = shortest_path_length - 1; i >= 0; i--)
	{
		p_shortest_path[i].col = p_goal_node->col;
		p_shortest_path[i].row = p_goal_node->row;
		p_goal_node = p_goal_node->p_parent;
	}

	return 1;
}

/*-----------------------------------------------------------------------------------
Clean up when complete
-----------------------------------------------------------------------------------*/

void CAStar::Shutdown()
{
	if (p_shortest_path != nullptr) {
		free(p_shortest_path);
		p_shortest_path = nullptr;
	}
}