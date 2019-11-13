all: serializer

serializer: main.o
	g++ main.o -o serializer

main.o : main.cpp
	g++ -c main.cpp --std=c++14

test: serializer
	./serializer

run: serializer
	./serializer	 
