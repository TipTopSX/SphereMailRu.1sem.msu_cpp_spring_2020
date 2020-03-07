all: lalloc

lalloc: main.o lalloc.o
	g++ main.o lalloc.o -o lalloc

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

lalloc.o: lalloc.cpp
	g++ -c lalloc.cpp --std=c++14

test: lalloc
	./lalloc

run: lalloc
	./lalloc