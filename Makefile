calc: src/poly.o src/main.cpp
	g++ --std=c++11 src/main.cpp src/poly.o -o calc  -lgmpxx -lgmp

poly.o: src/poly.cpp src/poly.h
	g++ -c --std=c++11 src/poly.cpp -o poly.o  -lgmpxx -lgmp


clean:
	rm poly.o calc
