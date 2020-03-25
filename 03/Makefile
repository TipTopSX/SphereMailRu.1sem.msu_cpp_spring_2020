all: myprogram

myprogram: main.o parse.o
	g++ main.o matrix.o -o myprogramr

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

matrix.o: matrix.cpp
	g++ -c matrix.cpp --std=c++14

test: myprogram
	./myprogramr

run: myprogram
	./myprogramr