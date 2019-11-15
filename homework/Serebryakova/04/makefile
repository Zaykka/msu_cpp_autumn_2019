all: big
big: bigInt.o main.o
	g++  main.o bigInt.o -o  big
main.o: main.cpp
	g++ -c main.cpp --std=c++14
bigInt.o: bigInt.cpp
	g++ -c bigInt.cpp --std=c++14
test: big
	./big

run: big
	./big
