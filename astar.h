#pragma once

#include "cell.h"
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
using namespace std;

#define ROW 10
#define COL 10

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

class AStar
{
private:
	//int row_;
	//int col_;
	string heuristic_;

public:
	AStar() {};
	AStar(string heuristic = "manhattan");

	bool isValid(int row, int col);
	bool isBlocked(Cell grid[][COL], int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	stack<Pair> TracePath(Cell map[][COL], Pair dest);
	void aStarSearch(Cell grid[][COL], Pair src, Pair dest);
};