#include "astar.h"



AStar::AStar(string heuristicType){
	heuristic_ = heuristicType;
//	row_ = row;
//	col_ = col;
}




bool AStar::isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) &&
		   (col >= 0) && (col < COL);
}




bool AStar::isBlocked(vector<vector<Cell>> map, int row, int col)
{
	return (map[row][col].isObstacle());
}




bool AStar::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}




double AStar::calculateHValue(int row, int col, Pair dest)
{
	if (heuristic_ == "manhattan")
		return (abs(row - dest.first) + abs(col - dest.second));

	else if (heuristic_ == "euclidean")
		return ((double)sqrt( (row - dest.first) * (row - dest.first) +  (col - dest.second) * (col - dest.second)));

}



void AStar::setHeuristic(string heuristicType)
{
	heuristic_ = heuristicType;
}





stack<Pair> AStar::TracePath(vector<vector<Cell>> map, Pair dest)
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




void AStar::aStarSearch(vector<vector<Cell>> map, Pair src, Pair dest)
{
	if (isValid(src.first, src.second) == false)
	{
		cout << "Source is invalid\n";
		return;
	}

	if (isValid(dest.first, dest.second) == false)
	{
		cout << "Destination is invalid\n";
		return;
	}

	if (isBlocked(map, src.first, src.second) == true ||
		isBlocked(map, dest.first, dest.second) == true)
	{
		cout << "Source or the destination is blocked\n";
		return;
	}

	if (isDestination(src.first, src.second, dest) == true)
	{
		cout << "We are already at the destination\n";
		return;
	}

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	int i, j;

	i = src.first, j = src.second;
	map[i][j].SetF(0.0);
	map[i][j].SetG(0.0);
	map[i][j].SetH(0.0);
	map[i][j].SetParentActualX(i);
	map[i][j].SetParentActualY(j);

	set<pPair> openList;

	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		for (int fila = -1; fila <= 1; fila++)
		{
			for (int col = -1; col <= 1; col++)
			{

				if ((i + fila == i - 1 && j + col == j) || (i + fila == i && j + col == j + 1) || (i + fila == i + 1 && j + col == j) || (i + fila == i && j + col == j - 1))
				{

					if (isValid(i + fila, j + col) == true)
					{
						if (isDestination(i + fila, j + col, dest) == true)
						{
							map[i + fila][j + col].SetParentActualX(i);
							map[i + fila][j + col].SetParentActualY(j);
							cout << "The destination cell is found\n";

							cout << "ANTES";
							cout << "HOLA";
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

	if (foundDest == false)
		cout << "Failed to find the Destination Cell\n";

	return;
}