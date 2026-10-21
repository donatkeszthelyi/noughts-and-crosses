main : main.o noughts_and_crosses.o
	g++ -g main.o noughts_and_crosses.o -o main

main.o : main.cpp noughts_and_crosses.h
	g++ -Wall -g -c main.cpp

noughts_and_crosses.o : noughts_and_crosses.cpp noughts_and_crosses.h
	g++ -Wall -g -c noughts_and_crosses.cpp
