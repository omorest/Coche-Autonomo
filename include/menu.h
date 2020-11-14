#include "../include/astar.h"
#include "../include/cell.h"
#include <string>

void FileReader(string file);
void ManualMode();

void createGrid(vector<vector<Cell>>& map, int& row, int& col);
void setEntryExit(vector<vector<Cell>>& map, Pair& entry, Pair& exit);
void printMap(vector<vector<Cell>> map);
