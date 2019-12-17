all: pool

pool: main.o
	g++ main.o -o

main.o:  main.cpp
	g++ -c main.cpp --std=c++14

test: pool
	./a.out

run: pool
	./a.out

clean:
	rm -rf *.o pool
