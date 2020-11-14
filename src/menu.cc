#include "../include/menu.h"

void FileReader(string file) {
  int row, col;
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



void ManualMode() {
  int row, col;
	Pair entry, exit;
  int option;
  vector<vector<Cell>> map;
  
  cout << "\nWelcome!";
  while (option != 5)
  {
    cout << "\n------------------------------------------------------------------------------\n";
    cout << "\nPlease enter some information of the map:\n";
    cout << "1. Dimensions\n";
    cout << "2. Entry and exit\n";
    cout << "3. Set obstacles\n";
    cout << "4. A* Algorithm\n";
    cout << "5. Exit\n";
    cout << "Enter the option: ";
    cin >> option;
    cout << "\n";

    switch (option)
    {
    case 1:
      createGrid(map, row, col);
      printMap(map);
      break;

    case 2:
      setEntryExit(map, entry, exit);
      printMap(map);
      break;

    case 3:
      CreateObastacles(map, row, col);
      printMap(map);
      break;

    case 4:
      RunAlgorithm(map, entry, exit);
      printMap(map);
      break;

    case 5:
      exit;
      break;

    default:
      cout << "Introduce a valid option: 1, 2, 3, 4, 5.\n";
    }
  }
}



void createGrid(vector<vector<Cell>>& map, int& row, int& col) {
  map.clear();

  cout << "Enter the number of the rows: ";
  cin >> row;
  map.resize(row);
  cout << "Enter the number of the columns: ";
  cin >> col;
  cout << "\n";
  
  for (int i = 0; i < row; i++)
    map[i].resize(col);
}



void setEntryExit(vector<vector<Cell>>& map, Pair& entry, Pair& exit) {
  cout << "Enter the position of the entry: \nRow: ";
  cin >> entry.first;
  cout << "\nCol: ";
  cin >> entry.second;
  cout << "\nEnter the position of the exit: \nRow: ";
  cin >> exit.first;
  cout << "\nCol: ";
  cin >> exit.second;
  cout << "\n";

  map[entry.first][entry.second].SetEntry();
  map[exit.first][exit.second].SetExit();
}



void RandomObstacles(vector<vector<Cell>>& map, int row, int col) {
  double percentage = 0.0;
  int obstacles_num;
  int x_random, y_random;

  cout << "What percentage of obstacles do you want?\n";
  cin >> percentage;

  percentage = percentage/100;
  obstacles_num = row * col * percentage;

  srand(time(NULL));

  int i = 0;
  while ((i < obstacles_num) && (obstacles_num <= ((row * col) - 2))) {
    x_random = (rand() % (row));
    y_random = (rand() % (col));
    map[x_random][y_random].SetObstacle(true);
    i++;
  }
}



void ManualObstacles(vector<vector<Cell>>& map, int row, int col) {
  bool more_obstacles = true;
  int x_obs, y_obs;
  string answer;

  do
  {
    cout << "Enter the obstacle position: \nx: ";
    cin >> x_obs;
    cout << "y: ";
    cin >> y_obs;
    cout << "\n";

    map[x_obs][y_obs].SetObstacle(true);
    do
    {
      cout << "Do you want to add more obstacles? y/n \n";
      cin >> answer;
    } while (answer != "y" && answer != "n");

    if (answer == "n")
      more_obstacles = false;
  } while (more_obstacles);
}



void CreateObastacles(vector<vector<Cell>>& map, int row, int col) {
  int option_obstacles = 0;

  do
  {
    cout << "Enter the way to enter obstacles:\nRandom - [1]\nManual - [2]\n";
    cin >> option_obstacles;
  } while (option_obstacles != 1 && option_obstacles != 2);

  if (option_obstacles == 1) 
    RandomObstacles(map, row, col);

  if (option_obstacles == 2)
    ManualObstacles(map, row, col);
}



void RunAlgorithm(vector<vector<Cell>>& map, Pair entry, Pair exit) {
  AStar algorithm("manhattan");
  string heuristic_type;
  int option_heuristic = 0;

  do
  {
    cout << "Enter the heuristic you want to use:\nManhattan - [1]\nEuclidean - [2]\n";
    cin >> option_heuristic;
    if (option_heuristic == 1)
      heuristic_type = "manhattan";
    if (option_heuristic == 2)
      heuristic_type = "euclidean";
  } while (option_heuristic != 1 && option_heuristic != 2);

  algorithm.setHeuristic(heuristic_type);
  algorithm.aStarSearch(map, entry, exit);
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
