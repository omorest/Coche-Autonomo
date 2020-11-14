#include "../include/astar.h"
#include "../include/menu.h"
#include <string>

// void printMap(vector<vector<Cell>> map);
int main(int argc, char *argv[]) {
	//Entrada de datos por fichero
	if (argc == 2) {
    string file = argv[1];
    FileReader(file);
  }
	//Entrada de datos manual
	else if (argc == 1)
    ManualMode();
}