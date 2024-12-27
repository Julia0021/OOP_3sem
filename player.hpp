#pragma once
#include "shipmanager.h"
#include "gamefield.h"
#include "ability_manager.h"

class Unit {
    protected:
        ShipManager& shipManager;
        GameField& field;
    public:
        Unit(ShipManager& shipManager, GameField& field)
            : shipManager(shipManager), field(field) {}

        virtual ShipManager& getShipManager() = 0;
        virtual GameField& getField() = 0;
        virtual ~Unit() {};
};

class Player : public Unit {
    private:
        AbilityManager& abilityManager;
    public:
        Player(ShipManager& shipManager, GameField& field, AbilityManager& abilityManager)
            : Unit(shipManager, field), abilityManager(abilityManager) {}
        Player(const Player& other)
            : Unit(other.shipManager, other.field), abilityManager(other.abilityManager) {}
        Player& operator=(const Player& other) {
            if (this != &other) {
                this->shipManager = other.shipManager;
                this->field = other.field;
                this->abilityManager = other.abilityManager;
            }
            return *this;
        }

        ShipManager& getShipManager() override { return shipManager; };
        GameField& getField() override { return field; };
        AbilityManager& getAbilityManager() { return abilityManager; };
};

class Enemy : public Unit {
    public:
        Enemy(ShipManager& shipManager, GameField& field)
            : Unit(shipManager, field) {}
        Enemy(const Enemy& other)
            : Unit(other.shipManager, other.field) {}

        Enemy& operator=(const Enemy& other) {
            if (this != &other) {
                this->shipManager = other.shipManager;
                this->field = other.field;
            }
            return *this;
        }

        ShipManager& getShipManager() override { return shipManager; };
        GameField& getField() override { return field; };
};