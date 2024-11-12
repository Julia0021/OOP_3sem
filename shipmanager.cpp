#include "shipmanager.h"

ShipManager::ShipManager(std::vector<unsigned>& shipLengths) {
    for (auto len : shipLengths) {
        ships.push_back(new Ship(len));
    }
};

int ShipManager::getShipsNum() const {
    return ships.size();
}

Ship* ShipManager::getShip(int ship_i) const {
    if (ship_i >= 0 && ship_i < ships.size()) {
        return ships[ship_i];
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

