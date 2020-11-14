#include "../include/menu.h"

void FileReader(string file, int row, int col) {

  int row_obstacle, col_obstacle;
  Pair entry, exit;

  ifstream is(file);
  is >> row >> col;

  vector<vector<Cell>> map(row, vector<Cell>(col));
  printMap(map);

  is >> entry.first >> entry.second;
  is >> exit.first >> exit.second;
  map[entry.first][entry.second].SetEntry();
  map[exit.first][exit.second].SetExit();

  printMap(map);

  while (!is.eof())
  {
    is >> row_obstacle >> col_obstacle;
    map[row_obstacle][col_obstacle].SetObstacle(true);
  }

  printMap(map);

  is.close();
  AStar algorithm("euclidean");
  algorithm.aStarSearch(map, entry, exit);

  printMap(map);  
}



//Imprimir mapa
void printMap(vector<vector<Cell>> map) {
  cout << endl << endl;
	for (int i = 0; i < map.size(); i++) {
	  for (int j = 0; j < map[i].size(); j++) {
		cout << map[i][j].GetEmoji();
	  }
	  cout << endl;
	}
  cout << endl;
}
