all: myprogram

myprogram: main.o parse.o
	g++ main.o filesort.o -o myprogramr

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

filesort.o: filesort.cpp
	g++ -c filesort.cpp --std=c++14

test: myprogram
	./myprogramr

run: myprogram
	./myprogramr