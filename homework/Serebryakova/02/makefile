all: allocator

allocator: main.o allocator.o
	g++ main.o allocator.o -o allocator

main.o: main.cpp 
	g++  -c main.cpp  --std=c++11 

allocator.o: allocator.cpp 
	g++ -c allocator.cpp --std=c++11 

test: allocator
	./allocator

run: allocator
	./allocator

