#pragma once

#include "cell.h"

#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

class AStar
{
private:
	string heuristic_;
	set<pPair> openList_;
	stack<Pair> path_;
	
public:
	AStar() {};
	AStar(string heuristic);

	bool isValid(const vector<vector<Cell>>& map, int row, int col);
	bool isBlocked(vector<vector<Cell>> map, int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	void TracePath(vector<vector<Cell>>& map, Pair dest);
	void aStarSearch(vector<vector<Cell>>& map, Pair src, Pair dest);
	void setHeuristic(string heuristicType);
	int getOpentListSize() const;
	int getPathSize() const;
};