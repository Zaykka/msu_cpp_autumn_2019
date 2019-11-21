all: format

format: main.o
	g++ main.o -o format
main.o:	main.cpp
	g++ -c main.cpp --std=c++14

test: format
	./foramt

run: format
	./format

clean:
	rm -rf *.o format
