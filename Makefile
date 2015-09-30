calc: poly.o main.cpp
	g++ --std=c++11 main.cpp poly.o -o calc  -lgmpxx -lgmp

poly.o: poly.cpp poly.h
	g++ -c --std=c++11 poly.cpp -o poly.o  -lgmpxx -lgmp


