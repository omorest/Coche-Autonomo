#include "../include/astar.h"



AStar::AStar(string heuristicType) {
	heuristic_ = heuristicType;
}



bool AStar::isValid(const vector<vector<Cell>>& map, int row, int col) {
	return (row >= 0) && (row < map.size()) && (col >= 0) && (col < map[0].size());
}




bool AStar::isBlocked(vector<vector<Cell>> map, int row, int col) {
	return (map[row][col].isObstacle());
}




bool AStar::isDestination(int row, int col, Pair dest) {
	if (row == dest.first && col == dest.second)
		return true;
	
  return false;
}



double AStar::calculateHValue(int row, int col, Pair dest) {
	if (heuristic_ == "manhattan")
		return (abs(row - dest.first) + abs(col - dest.second));

	else if (heuristic_ == "euclidean")
		return ((double)sqrt( (row - dest.first) * (row - dest.first) +  (col - dest.second) * (col - dest.second)));
}



void AStar::setHeuristic(string heuristicType) {
	heuristic_ = heuristicType;
}




void AStar::TracePath(vector<vector<Cell>>& map, Pair dest) {
	cout << "\nThe Path is ";
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path_copy;

	while (!(map[row][col].GetParentActualX() == row && map[row][col].GetParentActualY() == col))
	{
		Path_copy.push(make_pair(row, col));
		int temp_row = map[row][col].GetParentActualX();
		int temp_col = map[row][col].GetParentActualY();
		row = temp_row;
		col = temp_col;
	}

	Path_copy.push(make_pair(row, col));
	path_ = Path_copy; 
	while (!Path_copy.empty())
	{
		pair<int, int> p = Path_copy.top();
		Path_copy.pop();
    map[p.first][p.second].SetCellInPath();
		cout << "-> (" << p.first << ", " << p.second << ")";
	}

}



void AStar::aStarSearch(vector<vector<Cell>>& map, Pair src, Pair dest)
{
  const int ROW = map.size();
  const int COL = map[0].size();

	if (isValid(map, src.first, src.second) == false) {
		cout << "Source is invalid\n";
		return;
	}

	if (isValid(map, dest.first, dest.second) == false) {
		cout << "Destination is invalid\n";
		return;
	}

	if (isBlocked(map, src.first, src.second) == true ||
		isBlocked(map, dest.first, dest.second) == true)
	{
		cout << "Source or the destination is blocked\n";
		return;
	}

	if (isDestination(src.first, src.second, dest) == true) {
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


	openList_.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList_.empty())
	{
		pPair p = *openList_.begin();

		openList_.erase(openList_.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		for (int fila = -1; fila <= 1; fila++)
		{
			for (int col = -1; col <= 1; col++)
			{
				if ((i + fila == i - 1 && j + col == j) 
            || (i + fila == i && j + col == j + 1) 
            || (i + fila == i + 1 && j + col == j) 
            || (i + fila == i && j + col == j - 1))
				{
					if (isValid(map, i + fila, j + col) == true)
					{
						if (isDestination(i + fila, j + col, dest) == true) {
							map[i + fila][j + col].SetParentActualX(i);
							map[i + fila][j + col].SetParentActualY(j);
							cout << "The destination cell is found\n";

							TracePath(map, dest);
							foundDest = true;

							return;
						}

						else if (closedList[i + fila][j + col] == false 
                      && isBlocked(map, i + fila, j + col) == false)
						{
							gNew = map[i][j].GetG() + 1.0;
							hNew = calculateHValue(i + fila, j + col, dest);
							fNew = gNew + hNew;

							if (map[i + fila][j + col].GetF() == FLT_MAX ||
								map[i + fila][j + col].GetF() > fNew)
							{
								openList_.insert(make_pair(fNew, make_pair(i + fila, j + col)));

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



int AStar::getOpentListSize() const {
	return openList_.size();
}



int AStar::getPathSize() const {
	return path_.size();
}