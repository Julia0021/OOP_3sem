all: main.o
		g++ *.o -o main 
main.o: main.cpp ship.o shipmanager.o gamefield.o ability_manager.o game.o
		g++ -c -g main.cpp 
game.o: game.cpp game_state.o
		g++ -c -g game.cpp
game_state.o: game_state.cpp serialization.o deserialization.o wrapper.o
		g++ -c -g game_state.cpp
serialization.o: serialization.cpp *.h *.hpp
		g++ -c -g serialization.cpp
deserialization.o: deserialization.cpp *.h *.hpp
		g++ -c -g deserialization.cpp
wrapper.o: wrapper.cpp *.h *.hpp
		g++ -c -g wrapper.cpp
ship.o: ship.cpp ship.h
		g++ -c -g ship.cpp 
shipmanager.o: shipmanager.cpp shipmanager.h ship.h
		g++ -c -g shipmanager.cpp 
gamefield.o: gamefield.cpp gamefield.h field_exceptions.h ship.h coordinates.h
		g++ -c -g gamefield.cpp 
ability_manager.o: ability_manager.cpp double_damage.o random_ship_attack.o scanner.o abilities/*.h ability_exception.h ability_manager.h
		g++ -c -g ability_manager.cpp 
double_damage.o: abilities/double_damage.cpp abilities/double_damage.h 
		g++ -c -g abilities/double_damage.cpp 
random_ship_attack.o: abilities/random_ship_attack.cpp abilities/random_ship_attack.h
		g++ -c -g abilities/random_ship_attack.cpp 
scanner.o: abilities/scanner.cpp abilities/scanner.h
		g++ -c -g abilities/scanner.cpp 
clean:
		rm *.o main