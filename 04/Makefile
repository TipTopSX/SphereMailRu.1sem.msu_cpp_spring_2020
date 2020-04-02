all: myprogram

myprogram: main.o serializer.o
	g++ main.o matrix.o -o myprogramr

main.o: main.cpp
	g++ -c main.cpp --std=c++14

serializer.o: serializer.cpp
	g++ -c serializer.cpp --std=c++14

test: myprogram
	./myprogramr

run: myprogram
	./myprogramr