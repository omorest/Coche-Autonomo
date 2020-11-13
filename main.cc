#include "./astar.h"

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

		is >> entry.first >> entry.second;
		is >> exit.first >> exit.second;

		while (!is.eof())
		{
			is >> row_obstacle >> col_obstacle;
			map[row_obstacle][col_obstacle].SetObstacle(true);
		}

		is.close();
		AStar algorithm("euclidean");
		algorithm.aStarSearch(map, entry, exit);
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
				break;

			case 3:
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
				cout << "Good bye!\n";
				break;

			default:
				cout << "Introduce a valid option: 1, 2, 3, 4.\n";
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
