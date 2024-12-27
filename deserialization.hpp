#pragma once
#include "shipmanager.h"
#include "gamefield.h"
#include "ability_manager.h"
#include <string.h>
#include ".vscode/nlohmann/json.hpp"

class Deserialization {
    private:
        nlohmann::json& j; 
    public:
        Deserialization(nlohmann::json& j) : j(j) {};

        void from_json(ShipManager& shipManager, std::string key);
        void from_json(GameField& field, std::string key);
        void from_json(AbilityManager& abilityManager, std::string key);
};