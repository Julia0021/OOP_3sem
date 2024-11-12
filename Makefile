all: main.o ship.o shipmanager.o gamefield.o
		g++ *.o -o main 
main.o: main.cpp ship.o shipmanager.o gamefield.o *.h
		g++ -c main.cpp 
ship.o: ship.cpp 
		g++ -c ship.cpp 
shipmanager.o: shipmanager.cpp 
		g++ -c shipmanager.cpp 
gamefield.o: gamefield.cpp
		g++ -c gamefield.cpp 
clean:
		rm *.o main