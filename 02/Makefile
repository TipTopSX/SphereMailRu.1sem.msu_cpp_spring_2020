all: callbackparser

callbackparser: main.o parse.o
	g++ main.o parse.o -o callbackparser

main.o: main.cpp
	g++  -c main.cpp  --std=c++14

parse.o: parse.cpp
	g++ -c parse.cpp --std=c++14

test: callbackparser
	./callbackparser

run: callbackparser
	./callbackparser