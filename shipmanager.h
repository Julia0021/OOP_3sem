#pragma once
#include <vector>
#include "ship.h"

class ShipManager 
{
private:
    std::vector<Ship*> ships;
    unsigned destroyedShipsNum;

public:
    ShipManager(std::vector<unsigned>& shipLengths);

    ~ShipManager() {
        for (auto ship : ships) {
            delete ship;
        }
    }

    int getShipsNum() const;

    Ship* getShip(int ship_i) const;

    void getSegDamaged(int ship_i, int segment_i);

    bool areDestroyed();

    bool anotherShipDestroyed();
}; 