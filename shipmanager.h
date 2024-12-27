#pragma once
#include <vector>
#include <iostream>
#include "ship.h"

class ShipManager 
{
private:
    std::vector<Ship*> ships;
    unsigned destroyedShipsNum;

public:
    ShipManager() : ships({}) {};
    ShipManager(std::vector<unsigned>& shipLengths);

    ShipManager(const ShipManager& other) : destroyedShipsNum(other.destroyedShipsNum) {
        for (const auto& ship : other.ships) {
            ships.push_back(new Ship(ship->getLength(), ship->index));
        }
    }

    ShipManager& operator=(const ShipManager& other) {
        if (this != &other) {
            for (auto& ship : ships) {
                delete ship;
            }
            ships.clear();

            for (const auto& ship : other.ships) {
                Ship* newShip = new Ship(ship->getLength(), ship->index);
                for (int i = 0; i < ship->getLength(); ++i) {
                    if(ship->getSegStatus(i) != Ship::Segment::Intact) {
                        newShip->getSegDamaged(i);
                        if(ship->getSegStatus(i) == Ship::Segment::Destroyed) {
                            newShip->getSegDamaged(i);
                        }
                    }
                }
                ships.push_back(newShip);
            }

            destroyedShipsNum = other.destroyedShipsNum;
        }
        return *this;
    }

    ~ShipManager() {
        clear();
    }

    void clear() {
        for (auto& ship : ships) {
            delete ship;
        }
        ships.clear();
        destroyedShipsNum = 0;
    }

    int getShipsNum() const;

    Ship* getShip(int ship_i);

    void getSegDamaged(int ship_i, int segment_i);

    bool areDestroyed();

    bool anotherShipDestroyed();

    void setDestroyedShips(unsigned num);
}; 