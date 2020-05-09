all: program

program: main.o
	g++ main.o -o program

main.o: main.cpp
	g++ -c main.cpp --std=c++14

test: program
	./program

run: program
	./program