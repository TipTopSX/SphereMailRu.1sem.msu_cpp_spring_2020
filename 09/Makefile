all: program

program: main.o filesort.o
	g++ main.o filesort.o -o prog

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

filesort.o: filesort.cpp
	g++ -c filesort.cpp --std=c++14

test: program
	./prog

run: program
	./prog