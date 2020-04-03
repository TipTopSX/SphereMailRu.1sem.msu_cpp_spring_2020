all: myprogram

myprogram: main.o bigint.o
	g++ main.o bigint.o -o myprogram

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

bigint.o: bigint.cpp
	g++ -c bigint.cpp --std=c++14

test: myprogram
	./myprogram

run: myprogram
	./myprogram