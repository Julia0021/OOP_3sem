#include <iostream>
#include <vector>
#include "ship.h"
#include "shipmanager.h"
#include "gamefield.h"

int main() 
{
    GameField field(10, 10);

    std::vector<unsigned> v{1, 2, 4, 5};
    ShipManager manager(v);

    Ship* ship_ptr_4 = manager.getShip(2);
    field.setShip(ship_ptr_4, 1, 1, true);

    bool res = field.attack(1, 2);

    if (field.isCellOccupied(2, 1)) {
        std::cout << "Occupied\n";
    } else {
        std::cout << "Not occupied\n";
    }

    Ship::Segment attacked_status = manager.getShip(2)->getSegStatus(1);
    if (attacked_status == Ship::Segment::Damaged) {
        std::cout << "Damaged\n";
    } else {
        std::cout << "Intact\n";
    } 

    return 0;
}