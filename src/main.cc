#include "../include/astar.h"

void printMap(vector<vector<Cell>> map);
int main(int argc, char *argv[])
{
	int row, col;
	int row_obstacle, col_obstacle;
	Pair entry, exit;
	AStar algorithm("manhattan");

	//Entrada de datos por fichero
	if (argc == 2)
	{
		ifstream is(argv[1]);
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

	//Entrada de datos manual
	else if (argc == 1)
	{
		int option;
		bool more_obstacles;
		int x_obs, y_obs;
		string answer;
		vector<vector<Cell>> map;
		string heuristic_type;
		int option_heuristic = 0;
		int option_obstacles = 0;
		double percentage = 0;
		int x_random, y_random;
		int obstacles_num;
		int i = 0;

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
				cout << "Enter the number of the rows: ";
				cin >> row;
				map.resize(row);

				cout << "Enter the number of the columns: ";
				cin >> col;
				cout << "\n";

				for (int i = 0; i < row; i++)
				{
					map[i].resize(col);
				}

				printMap(map);

				break;

			case 2:
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

				printMap(map);

				break;

			case 3:
				do
				{
					cout << "Enter the way to enter obstacles:\nRandom - [1]\nManual - [2]\n";
					cin >> option_obstacles;
				} while (option_obstacles != 1 && option_obstacles != 2);

				if (option_obstacles == 1) {
					cout << "What percentage of obstacles do you want?\n";
					cin >> percentage;

					percentage = percentage/100;
					obstacles_num = row * col * percentage;
					
					srand(time(NULL));
					while ((i < obstacles_num) && (obstacles_num <= ((row * col) - 2))) {
						x_random = (rand() % (row)); 
						y_random = (rand() % (col)); 
						map[x_random][y_random].SetObstacle(true);
						i++;
					}
					
				}

				if (option_obstacles == 2) {
					more_obstacles = true;
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

				printMap(map);
				break;

			case 4:
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


				break;

			case 5:
				exit;
				break;

			default:
				cout << "Introduce a valid option: 1, 2, 3, 4, 5.\n";
			}
		}
	}

	//Cell grid[ROW][COL];
	//grid[0][3].SetObstacle(true);
	//grid[8][9].SetObstacle(true);
	//grid[2][3].SetObstacle(true);
	//grid[0][0].SetObstacle(true);

	//Pair src = make_pair(0, 0);
	//
	//Pair dest = make_pair(9, 9);
}


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
