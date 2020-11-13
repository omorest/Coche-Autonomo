#include "astar.h"



AStar::AStar(string heuristicType){
	heuristic_ = heuristicType;
//	row_ = row;
//	col_ = col;
}

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool AStar::isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) &&
		   (col >= 0) && (col < COL);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool AStar::isBlocked(Cell grid[][COL], int row, int col)
{
	// Returns true if the cell is not blocked else false
	return (grid[row][col].isObstacle());
}

// A Utility Function to check whether destination cell has
// been reached or not
bool AStar::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double AStar::calculateHValue(int row, int col, Pair dest)
{
	if (heuristic_ == "manhattan")
		return (abs(row - dest.first) + abs(col - dest.second));

	else if (heuristic_ == "euclidean")
		return ((double)sqrt( (row - dest.first) * (row - dest.first) +  (col - dest.second) * (col - dest.second)));
	
}

// A Utility Function to trace the path from the source
// to destination
stack<Pair> AStar::TracePath(Cell map[][COL], Pair dest)
{
	cout << "\nThe Path is ";
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;
	stack<Pair> Path_copy;

	while (!(map[row][col].GetParentActualX() == row && map[row][col].GetParentActualY() == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = map[row][col].GetParentActualX();
		int temp_col = map[row][col].GetParentActualY();
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	Path_copy = Path; 
	while (!Path.empty())
	{
		pair<int, int> p = Path.top();
		Path.pop();
		cout << "-> (" << p.first << ", " << p.second << ")";
	}

	return Path_copy;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void AStar::aStarSearch(Cell map[][COL], Pair src, Pair dest)
{
	// If the source is out of range
	if (isValid(src.first, src.second) == false)
	{
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (isValid(dest.first, dest.second) == false)
	{
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (isBlocked(map, src.first, src.second) == true ||
		isBlocked(map, dest.first, dest.second) == true)
	{
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest) == true)
	{
		printf("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which means
	// that no cell has been included yet
	// This closed list is implemented as a boolean 2D array
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details
	//of that cell
	//Cell map[ROW][COL];

	int i, j;

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	map[i][j].SetF(0.0);
	map[i][j].SetG(0.0);
	map[i][j].SetH(0.0);
	map[i][j].SetParentActualX(i);
	map[i][j].SetParentActualY(j);

	/* 
	Create an open list having information as- 
	<f, <i, j>> 
	where f = g + h, 
	and i, j are the row and column index of that cell 
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	This open list is implenented as a set of pair of pair.*/
	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		// To store the 'g', 'h' and 'f' of the 8 successors
		double gNew, hNew, fNew;

		//Probando a usar el for de visitar a vecinas
		for (int fila = -1; fila <= 1; fila++)
		{
			for (int col = -1; col <= 1; col++)
			{

				//Visita solamente N, S, E, O
				if ((i + fila == i - 1 && j + col == j) || (i + fila == i && j + col == j + 1) || (i + fila == i + 1 && j + col == j) || (i + fila == i && j + col == j - 1))
				{

					if (isValid(i + fila, j + col) == true)
					{
						if (isDestination(i + fila, j + col, dest) == true)
						{
							// Set the Parent of the destination cell
							map[i + fila][j + col].SetParentActualX(i);
							map[i + fila][j + col].SetParentActualY(j);
							printf("The destination cell is found\n");

							TracePath(map, dest);
							foundDest = true;

							return;
						}

						else if (closedList[i + fila][j + col] == false &&
								 isBlocked(map, i + fila, j + col) == false)
						{
							gNew = map[i][j].GetG() + 1.0;
							hNew = calculateHValue(i + fila, j + col, dest);
							fNew = gNew + hNew;

							if (map[i + fila][j + col].GetF() == FLT_MAX ||
								map[i + fila][j + col].GetF() > fNew)
							{
								openList.insert(make_pair(fNew, make_pair(i + fila, j + col)));

								// Update the details of this cell
								map[i + fila][j + col].SetF(fNew);
								map[i + fila][j + col].SetG(gNew);
								map[i + fila][j + col].SetH(hNew);
								map[i + fila][j + col].SetParentActualX(i);
								map[i + fila][j + col].SetParentActualY(j);
							}
						}
					}
				}
			}
		}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destiantion cell. This may happen when the
	// there is no way to destination cell (due to blockages)
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}

// Driver program to test above function