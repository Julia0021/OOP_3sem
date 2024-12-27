#include "serialization.hpp"
#include <fstream>

void Serialization::to_json(ShipManager& shipManager, std::string key) {
    nlohmann::json jsm = nlohmann::json{};

    for (int i = 0; i < shipManager.getShipsNum(); i++) {
        Ship* temp = shipManager.getShip(i);
        std::string key = "ship" + std::to_string(i);
        jsm[key] = {
            {"length", temp->getLength()},
            {"horizontal", temp->isHorizontal()},
            {"index", temp->index},
            {"segments", nlohmann::json::array()}
        }; 

        for (int j = 0; j < temp->getLength(); j++) {
            Ship::Segment tempSegment = temp->getSegStatus(j);
            jsm[key]["segments"].push_back({
                {"status", tempSegment}
            });
        }
    }

    j[key] = jsm;
}

void Serialization::to_json(GameField& field, std::string key) {
    nlohmann::json jf = nlohmann::json{};

    jf["width"] = field.getWidth();
    jf["height"] = field.getHeight();

    std::vector<std::vector<GameField::Cell>> temp = field.getField();
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            jf[key] = {
                {"status", temp[y][x].getStatus()},
                {"index", temp[y][x].getShipSegIndex()},
                {"shipIndex", temp[y][x].getShipIndex()}
            };
        }
    }

    j[key] = jf;
}

void  Serialization::to_json(AbilityManager& abilityManager, std::string key) {
    nlohmann::json jam = nlohmann::json{};

    if (abilityManager.queueIsEmpty()) {
        jam["abilities"].push_back("");
    } else {
        for (int i = 0; i < abilityManager.getQueueSize(); i++) {
            jam["abilities"].push_back(
                abilityManager.getAbility(i).getName()
            );
        }
    }

    j[key] = jam;
}