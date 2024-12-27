#include "deserialization.hpp"

void Deserialization::from_json(ShipManager& shipManager, std::string key) {
    const auto& jsm = j.at(key);
    std::vector<unsigned> shipSizes;

    for (const auto& jship : jsm) {
        shipSizes.push_back(jship.at("length"));
    }

    ShipManager tempShipManager(shipSizes);
    shipManager = tempShipManager;

    for (size_t i = 0; i < shipSizes.size(); i++) {
        std::string key = "ship" + std::to_string(i);
        Ship* ship = shipManager.getShip(i);
        if (jsm.at(key).at("horizontal") == false) {
            ship->changePosition();
        }

        ship->index = jsm.at(key).at("index");

        for (int j = 0; j < shipSizes[i]; j++) {
            if (jsm.at(key).at("segments").at(j).at("status") != Ship::Segment::Intact) {
                ship->getSegDamaged(j);
                if (jsm.at(key).at("segments").at(j).at("status") == Ship::Segment::Destroyed) {
                    ship->getSegDamaged(j);
                }
            }
        }
    }

    unsigned destroyedShipsNum = 0;
    for (size_t i = 0; i < shipSizes.size(); i++) {
        Ship* ship = shipManager.getShip(i);
        if (ship->isDestroyed()) {
            destroyedShipsNum++;
        }
    }
    shipManager.setDestroyedShips(destroyedShipsNum);
}

void Deserialization::from_json(GameField& field, std::string key) {
    const auto& jf = j.at(key);
    field = GameField(jf.at("width"), jf.at("height"));

    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            GameField::Cell& cell = field.getCell(x, y);
            cell.setStatus(jf.at(key).at("status"));
            cell.setShipSegIndex(jf.at(key).at("index"));
            cell.setShipIndex(jf.at(key).at("shipIndex"));
        }
    }
}

void Deserialization::from_json(AbilityManager& abilityManager, std::string key) {
    const auto& jam = j.at(key);
    abilityManager = AbilityManager();
    abilityManager.clearQueue();
    
    for (const auto& jability : jam.at("abilities")) {
       if (jability == "Double Damage") {
           abilityManager.addAbility(new DoubleDamage());
       }
       else if(jability == "Scanner"){
           abilityManager.addAbility(new Scanner());
       }
       else if (jability == "Random Attack") {
           abilityManager.addAbility(new RandomAttack());
       }
    }
}