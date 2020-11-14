#pragma once

#define ROW 200
#define COL 200

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

public:
	AStar() {};
	AStar(string heuristic);

	bool isValid(int row, int col);
	bool isBlocked(vector<vector<Cell>> map, int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	stack<Pair> TracePath(vector<vector<Cell>> map, Pair dest);
	void aStarSearch(vector<vector<Cell>> map, Pair src, Pair dest);
	void setHeuristic(string heuristicType);
};