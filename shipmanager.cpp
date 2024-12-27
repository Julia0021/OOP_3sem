#include "shipmanager.h"

ShipManager::ShipManager(std::vector<unsigned>& shipLengths) {
    for (int i=0; i<shipLengths.size(); i++) {
        ships.push_back(new Ship(shipLengths[i], i));
    }
    destroyedShipsNum = 0;
};

int ShipManager::getShipsNum() const {
    return ships.size();
}

Ship* ShipManager::getShip(int ship_i) {
    for(auto ship : ships) {
        if(ship->index == ship_i) return ship;
    }
    return nullptr;
}

void ShipManager::getSegDamaged(int ship_i, int segment_i) {
    if (ship_i >= 0 && ship_i < ships.size()) {
        ships[ship_i]->getSegDamaged(segment_i);
    }
}

bool ShipManager::areDestroyed() {
    for (auto ship : ships) {
        if (!ship->isDestroyed()) return false;
    }
    return true;
}

bool ShipManager::anotherShipDestroyed() {
    unsigned curDestroyedShipNum = 0;
    for (Ship* ship : ships) {
        if (ship->isDestroyed()) {
            curDestroyedShipNum++;
        }
    }

    if (curDestroyedShipNum == this->destroyedShipsNum) {
        return false;
    }

    this->destroyedShipsNum = curDestroyedShipNum;

    return true;
}

void ShipManager::setDestroyedShips(unsigned num) {
    this->destroyedShipsNum = num;
}