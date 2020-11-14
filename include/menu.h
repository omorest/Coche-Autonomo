#include "../include/astar.h"
#include "../include/cell.h"
#include <string>
#include <chrono> 

using namespace std;
using namespace std::chrono;

void FileReader(string file);
void ManualMode();

void createGrid(vector<vector<Cell>>& map, int& row, int& col);
void setEntryExit(vector<vector<Cell>>& map, Pair& entry, Pair& exit);
void RandomObstacles(vector<vector<Cell>>& map, int row, int col);
void ManualObstacles(vector<vector<Cell>>& map, int row, int col);
void CreateObastacles(vector<vector<Cell>>& map, int row, int col);
void RunAlgorithm(vector<vector<Cell>>& map, Pair entry, Pair exit);
bool isValidCell(int row_map, int col_map, int row, int col);
void printMap(vector<vector<Cell>> map);
void showExperimentalTable(const AStar& algorithm, double duration);
  

