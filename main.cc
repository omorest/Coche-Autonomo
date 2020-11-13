#include "./astar.h"


int main() 
{ 
	/* Description of the Grid- 
	1--> The cell is not blocked 
	1--> The cell is blocked */
	int grid[ROW][COL] = 
	{ 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
	}; 

	// Source is the left-most bottom-most corner 
	Pair src = make_pair(0, 0); 

	// Destination is the left-most top-most corner 
	Pair dest = make_pair(9, 9); 

	aStarSearch(grid, src, dest);  
}