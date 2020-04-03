all: myprogram

myprogram: main.o
	g++ main.o -o myprogram

main.o: main.cpp
	g++ -c main.cpp --std=c++14

test: myprogram
	./myprogram

run: myprogram
	./myprogram