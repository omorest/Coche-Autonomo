#include "./astar.h"

int main()
{
	/* Description of the Grid- 
	1--> The cell is not blocked 
	1--> The cell is blocked */  
	Cell grid[ROW][COL];
    grid[0][3].SetObstacle(true);
    grid[8][9].SetObstacle(true);
    grid[2][3].SetObstacle(true);
    //grid[0][0].SetObstacle(true);





	// Source is the left-most bottom-most corner
	Pair src = make_pair(0, 0);

	// Destination is the left-most top-most corner
	Pair dest = make_pair(9, 9);

	AStar algorithm("euclidean");

	algorithm.aStarSearch(grid, src, dest);
}