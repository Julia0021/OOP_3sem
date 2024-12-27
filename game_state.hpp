#pragma once

#include "serialization.hpp"
#include "deserialization.hpp"
#include "player.hpp"
#include "wrapper.hpp"
#include "file_exceptions.h"

#include <fstream>

class GameState {
    private:
        Player& player;
        Enemy& enemy;
    public:
        GameState(Player& player, Enemy& enemy) : player(player), enemy(enemy) {};
        
        std::string getHash(const std::string& data);
        void placeShips(ShipManager& shipManager, GameField& field);
        
        void loadGame(const std::string& file);
        void saveGame(const std::string& file);

        Player& getPlayer() { return this->player; };
        Enemy& getEnemy() { return this->enemy; }
};