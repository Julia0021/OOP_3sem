#include <iostream>
#include <vector>
#include <limits>
#include "ship.h"
#include "shipmanager.h"
#include "gamefield.h"
#include "ability_manager.h"
#include "field_exceptions.h"
#include "ability_exception.h"

int main() 
{
    GameField field(10, 10);
    AbilityManager ability_manager;

    std::vector<unsigned> v{1, 2, 4, 5};
    ShipManager ship_manager(v);

    Ship* ship_ptr_4 = ship_manager.getShip(2);
    Ship* ship_ptr_2 = ship_manager.getShip(1);
    Ship* ship_ptr_5 = ship_manager.getShip(3);

    try {
    field.setShip(ship_ptr_4, 3, 1, false);
    field.setShip(ship_ptr_2, 0, 2, true);
    field.setShip(ship_ptr_5, 7, 0, true);
    } catch(const ShipOutsideTheFieldException& e) {
        std::cerr << e.what();
    } catch(const ShipsClosePlacementException& e) {
        std::cerr << e.what();
    }

    field.printField();
    std::string command;
    int x, y;

    bool gameover = false;
    while(!gameover) {
        if (ship_manager.anotherShipDestroyed()) {
            ability_manager.addAbility();
        }

        std::cout << "Enter your command (attack / ability / quit): ";
        std::cin >> command;

        if (command == "attack") {
            std::cout << "Please enter the coordinates (x, y): ";
            std::cin >> x >> y;

            if (std::cin.fail()) {
                std::cerr << "Bad input.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            try {
                field.attack(x, y);
                field.printField();
            } catch(const AttackOutsideTheFieldException& e) {
                std::cerr << e.what() << '\n';
            }
        } else if (command == "ability") {

            try {
                ability_manager.useAbility(field);
                field.printField();
            } catch(const EmptyAbilitiesException& e) {
                std::cerr << e.what() << '\n';
            }
        } else if (command == "quit") {
            gameover = true;
        } else {
            std::cerr << "Incorrect command\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }

    return 0;
}