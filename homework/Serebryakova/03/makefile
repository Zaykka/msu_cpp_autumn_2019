all: matrix

matrix: tests.o matrix.o
	g++ tests.o matrix.o -o matrix

test.o: tests.cpp
	g++ -c tests.cpp --std=c++14

matrix.o: matrix.cpp
	g++ -c matrix.cpp --std=c++14

test: matrix
	./matrix

run: matrix
	./matrix
