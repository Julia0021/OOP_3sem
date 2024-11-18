all: main.o
		g++ *.o -o main 
main.o: main.cpp ship.o shipmanager.o gamefield.o ability_manager.o *.h
		g++ -c main.cpp 
ship.o: ship.cpp 
		g++ -c ship.cpp 
shipmanager.o: shipmanager.cpp 
		g++ -c shipmanager.cpp 
gamefield.o: gamefield.cpp
		g++ -c gamefield.cpp 
ability_manager.o: ability_manager.cpp double_damage.o random_ship_attack.o scanner.o abilities/*.h
		g++ -c ability_manager.cpp 
double_damage.o: abilities/double_damage.cpp
		g++ -c abilities/double_damage.cpp 
random_ship_attack.o: abilities/random_ship_attack.cpp
		g++ -c abilities/random_ship_attack.cpp 
scanner.o: abilities/scanner.cpp
		g++ -c abilities/scanner.cpp 
clean:
		rm *.o main