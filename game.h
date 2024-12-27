#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>

#include "gamefield.h"
#include "ability_manager.h"
#include "shipmanager.h"
#include "coordinates.h"
#include "field_exceptions.h"
#include "ability_exception.h"
#include "player.hpp"
#include "game_state.hpp"

class Game {
public:
    Game(Player& player, Enemy& enemy, GameState& gameState, std::vector<unsigned>& shipSizes)
        : player(player), enemy(enemy), gameState(gameState), shipSizes(shipSizes) {
            this->file = "savefile.json";
            isPlayerWin = false;
            isBotWin = false;
            gameover = false;
        };

    void startGame();

    void setPlayerShips(std::vector<unsigned>& shipSizes);

    void setShips(std::vector<unsigned>& shipSizes, Unit& unit);

    void gameLoop();

    bool playerTurn(bool& player_turn);

    void enemyTurn();

    void resetBot();

    void resetGame();

    void isGameEnded();

    void loadGame(const std::string& file);

    void saveGame(const std::string& file);

private:
    Player& player; 
    Enemy& enemy;
    GameState& gameState;
    std::vector<unsigned>& shipSizes;
    std::string file;
    bool isPlayerWin;
    bool isBotWin;
    bool gameover;
};