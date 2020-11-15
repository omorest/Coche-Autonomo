SRC = src/
SRC_PROGRAM = $(SRC)main.cc $(SRC)astar.cc $(SRC)menu.cc $(SRC)cell.cc
OUT = bin/
OUT_MAIN_FILE = $(OUT)main

run: default

default:
	g++ -g $(SRC_PROGRAM) -o $(OUT_MAIN_FILE)

#Borramos lo creado anteriormente
clean:
	-rm bin/*
