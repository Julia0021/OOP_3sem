#pragma once
#include <string.h>
#include ".vscode/nlohmann/json.hpp"
#include "shipmanager.h"
#include "gamefield.h"
#include "ability_manager.h"

class Serialization {
    private:
        nlohmann::json& j; 
    public:
        Serialization(nlohmann::json& j) : j(j) {};

        void to_json(ShipManager& shipManager, std::string key);
        void to_json(GameField& field, std::string key);
        void to_json(AbilityManager& abilityManager, std::string key);
};