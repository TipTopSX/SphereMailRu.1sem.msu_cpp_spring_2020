all: program

program: main.o format.o
	g++ main.o format.o -o program

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

format.o: format.cpp
	g++ -c format.cpp --std=c++14

test: program
	./program

run: program
	./program