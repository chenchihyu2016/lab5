all: main.o solve.o
	g++ main.o solve.o -std=c++11 -o solve
main.o: main.cpp solve.h
	g++ -c -std=c++11 main.cpp
solve.o: solve.cpp solve.h
	g++ -c -std=c++11 solve.cpp
clean:
	rm **.o
