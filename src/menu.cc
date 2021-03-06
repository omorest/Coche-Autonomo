#define MAX_ROW 200
#define MAX_COL 200

#include "../include/menu.h"


void FileReader(string file) {
  int row, col;
  int row_obstacle, col_obstacle;
  string heuristic_type = "";
  string obstacle_mode = "";
  Pair entry, exit;

  ifstream is(file);
  is >> row >> col;

  if (row > MAX_ROW  &&  col > MAX_COL) {
    cout << "The introduced dimensions for map are out of the maximum range!\n";

    return;
  }

  vector<vector<Cell>> map(row, vector<Cell>(col));
  printMap(map);
  is >> entry.first >> entry.second;
  is >> exit.first >> exit.second;
  if (isValidCell(row, col, entry.first, entry.second)) {
    map[entry.first][entry.second].SetEntry();
  }

  if (isValidCell(row, col, exit.first, exit.second)) {
    map[exit.first][exit.second].SetExit();
  }

  printMap(map);

  is >> heuristic_type;
  is >> obstacle_mode;

  if (obstacle_mode == "manual") {
    while (!is.eof())
    {
      is >> row_obstacle >> col_obstacle;
      if (isValidCell(row, col, row_obstacle, col_obstacle)) {
        map[row_obstacle][col_obstacle].SetObstacle(true);
      }    
    }
  }
  else  if (obstacle_mode == "random") {
    double percent = 0.0;
    is >> percent;
    RandomObstacles(map, row, col, percent);
  }  


  printMap(map);
  AStar algorithm(heuristic_type);

  auto start = high_resolution_clock::now();
  algorithm.aStarSearch(map, entry, exit);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  showExperimentalTable(algorithm, duration.count());

  printMap(map);
  
  is.close();
}



void ManualMode() {
  int row, col;
	Pair entry, exit;
  char option;
  vector<vector<Cell>> map;
  
  cout << "\n\033[1;34mWelcome!\033[0m\n";
  while (option != 'n')
  {
    for (int i = 0; i < map.size(); i++)
      map[i].clear();
    map.clear();   

    cout << "\n------------------------------------------------------------------------------\n";
    cout << "\n\033[1;36mPlease enter some information of the map:\033[0m\n";
    cout << "\n\033[1;36m1. Dimensions\033[0m\n";
    createGrid(map, row, col);
    printMap(map);

    cout << "\033[1;36m2. Entry and exit\033[0m\n";
    setEntryExit(map, entry, exit);
    printMap(map);

    cout << "\033[1;36m3. Set obstacles\033[0m\n";
    CreateObastacles(map, row, col);
    printMap(map);

    cout << "\033[1;36m4. A* Algorithm\033[0m\n";
    RunAlgorithm(map, entry, exit);
    printMap(map);

    
    cout << "\033[1;36mDo you want to repeat the process? [y/n]\033[0m\n";
    cin >> option;
    cout << "\n";

  }
}



void createGrid(vector<vector<Cell>>& map, int& row, int& col) {
  do {
    cout << "Enter the number of the rows (MAX 200 rows): ";
    cin >> row;
  } while (row > MAX_ROW);

  map.resize(row);

  do {
    cout << "Enter the number of the columns (MAX 200 cols): ";
    cin >> col;
  } while (col > MAX_COL);
  
  cout << "\n";

  for (int i = 0; i < row; i++)
    map[i].resize(col);
}



void setEntryExit(vector<vector<Cell>>& map, Pair& entry, Pair& exit) {

  do
  {
    cout << "Enter the position of the entry: \nRow: ";
    cin >> entry.first;
    cout << "Col: ";
    cin >> entry.second;
    cout << "\n";

  } while(!isValidCell(map.size(), map[0].size(), entry.first, entry.second));

  map[entry.first][entry.second].SetEntry();

  do
  {
  cout << "\nEnter the position of the exit: \nRow: ";
  cin >> exit.first;
  cout << "Col: ";
  cin >> exit.second;
  cout << "\n";
    
  } while(!isValidCell(map.size(), map[0].size(), exit.first, exit.second));

  map[exit.first][exit.second].SetExit();
}



void RandomObstacles(vector<vector<Cell>>& map, int row, int col, double percent) {
  double percentage = percent;
  int obstacles_num;
  int x_random, y_random;

  if (percent == 0.0) {
    cout << "What percentage of obstacles do you want?\n";
    cin >> percentage;
  }
  

  percentage = percentage/100;
  obstacles_num = row * col * percentage;

  srand(time(NULL));

  int i = 0;
  while ((i < obstacles_num) && (obstacles_num <= ((row * col) - 2))) {

    do
    {
      x_random = (rand() % (row));
      y_random = (rand() % (col));      

    } while(!isValidCell(row, col, x_random, y_random) || map[x_random][y_random].isEntry()
            || map[x_random][y_random].isExit() || map[x_random][y_random].isObstacle());
    
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
    do
    {  
      cout << "Enter the obstacle position: \nx: ";
      cin >> x_obs;
      cout << "y: ";
      cin >> y_obs;
      cout << "\n";
    } while(!isValidCell(row, col, x_obs, y_obs));

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
    cout << "Enter the way to enter obstacles:\n[0] - Without Obstacles\n[1] - Random \n[2] - Manual\n";
    cin >> option_obstacles;
  } while (option_obstacles != 0 && option_obstacles != 1 && option_obstacles != 2);

  if (option_obstacles == 0)
    return;  
  
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

  auto start = high_resolution_clock::now();
  algorithm.aStarSearch(map, entry, exit);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  showExperimentalTable(algorithm, duration.count());
}


bool isValidCell(int row_map, int col_map, int row, int col) {
  if ((row >= 0) && (row < row_map) && (col >= 0) && (col < col_map)) {
    return true;
  }
  
  cout << "This position is out of range" << endl;
  return false;  
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



void showExperimentalTable(const AStar& algorithm, double duration) {
  cout << endl << "\nOPEN LIST SIZE: " << algorithm.getOpentListSize() << endl;
  cout << "PATH SIZE: " << algorithm.getPathSize() << endl;
  cout << "TIEMPO: " << duration/1000 << " s" << endl;
}