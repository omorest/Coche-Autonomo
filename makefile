main: main.o astar.o cell.o
	g++ -o main main.o astar.o cell.o 

#Creamos los objetos

main.o: ./src/main.cc
	g++ -c ./src/main.cc

astar.o: ./src/astar.cc
	g++ -c ./src/astar.cc

cell.o: ./src/cell.cc
	g++ -c ./src/cell.cc


#Borramos lo creado anteriormente
clean:
	-rm *.o main  
