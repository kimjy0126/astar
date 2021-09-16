all: main.cpp node.cpp coord.cpp node.h coord.h
	g++ -o astar main.cpp node.cpp coord.cpp
