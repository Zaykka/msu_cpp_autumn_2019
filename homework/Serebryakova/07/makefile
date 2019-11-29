all: vector

vector: main.o
	g++ main.o -o
	
main.o: main.cpp
	g++ -c main.cpp --std=c++14
	
test: vector
	./vector

run: vector
	./vector
	
clean:
	rm -rf *.o vector
