#include "game.h"

void Game::startGame() {
    setShips(shipSizes, player);
    setShips(shipSizes, enemy);
    gameLoop();
}

void Game::setShips(std::vector<unsigned>& shipSizes, Unit& unit) {
    // Получение случайной последовательности координат поля
    std::vector<Coords> unit_coords;
    for(int y=0; y<unit.getField().getHeight(); y++) {
        for(int x=0; x<unit.getField().getWidth(); x++) {
            Coords coords = {x, y};
            unit_coords.push_back(coords);
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(unit_coords.begin(), unit_coords.end(), gen);

    // Размещение кораблей 
    Ship* ship_ptr;
    bool pos_flag;
    bool ship_is_placed;
    for (size_t i=0; i < shipSizes.size(); i++) {
        ship_ptr = unit.getShipManager().getShip(i);
        ship_is_placed = false;
        std::uniform_int_distribution<> distrib(0, 1);
        pos_flag = (distrib(gen) == 1) ? true : false;

        for (size_t j=0; j < unit_coords.size(); j++) {
            ship_is_placed = true;
            try {
                unit.getField().setShip(ship_ptr, unit_coords[j].x, unit_coords[j].y, pos_flag);
            } catch(const ShipOutsideTheFieldException& e) {
                ship_is_placed = false;
            } catch(const ShipsClosePlacementException& e) {
                ship_is_placed = false;
            }
            if(ship_is_placed) break;

            ship_is_placed = true;
            try {
                unit.getField().setShip(ship_ptr, unit_coords[j].x, unit_coords[j].y, !pos_flag);
            } catch(const ShipOutsideTheFieldException& e) {
                ship_is_placed = false;
            } catch(const ShipsClosePlacementException& e) {
                ship_is_placed = false;
            }
            if(ship_is_placed) break;
        }
    }
}

void Game::gameLoop() {
    bool player_turn = false;
    while(!gameover) {
        std::cout << "Player turn.\n";
        enemy.getField().printField(true);
        while(!playerTurn(player_turn)) {
            std::cout << "Try again.\n";
        }
        if(gameover) break;

        if(player_turn) continue;
        enemy.getField().printField(true);
        std::cout << "Enemy turn.\n";
        player.getField().printField();
        enemyTurn();
        player.getField().printField();
        if(gameover) break;
    }
    std::cout << "Game Over!\n";
}

bool Game::playerTurn(bool& player_turn) {
    std::string command;
    int x, y;

    if (enemy.getShipManager().anotherShipDestroyed()) {
        player.getAbilityManager().addAbility();
    }

    std::cout << "Enter your command (attack / ability / quit / load / save): ";
    std::cin >> command;

    if (command == "attack") {
        std::cout << "Please enter the coordinates (x, y): ";
        std::cin >> x >> y;

        if (std::cin.fail()) {
            std::cerr << "Bad input.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }

        try {
            enemy.getField().attack(x, y);
            player_turn = false;
        } catch(const AttackOutsideTheFieldException& e) {
            std::cerr << e.what() << '\n';
            return false;
        }
    } else if (command == "ability") {

        try {
            player.getAbilityManager().useAbility(enemy.getField());
            player_turn = false;
        } catch(const EmptyAbilitiesException& e) {
            std::cerr << e.what() << '\n';
            return false;
        }
    } else if (command == "quit") {
        gameover = true;
    } else if (command == "load") {
        player_turn = true;
        std::cout << "Loading the game.\n";
        this->loadGame(file);
    } else if (command == "save") {
        player_turn = true;
        std::cout << "Saving the game." << std::endl;
        this->saveGame(file);
    } else {
        std::cerr << "Incorrect command." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    if(enemy.getShipManager().areDestroyed()) {
        this->isPlayerWin = true;
        std::cout << "You won!\n";
        isGameEnded();
    }
    return true;
}

void Game::enemyTurn() {
    std::vector<Coords> cells_coords;
    player.getField().getDamagedCellsCoords(cells_coords);

    if(cells_coords.empty()) {
        player.getField().getNotDestroyedCellsCoords(cells_coords);
    }

    if (cells_coords.empty()) {
        isGameEnded();
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cells_coords.begin(), cells_coords.end(), gen);

    auto firstPair = cells_coords.front();
    int randomX = firstPair.x;
    int randomY = firstPair.y;
    player.getField().attack(randomX, randomY);

    GameField::Cell cell = player.getField().getCell(randomX, randomY);
    if (cell.getStatus() == GameField::Cell::CellStatus::occupied) {
        int index = cell.getShipSegIndex();
        if(player.getShipManager().areDestroyed()) {
            this->isBotWin = true;
            std::cout << "You lost.\n";
            isGameEnded();
        }
    } 
    return;
}

void Game::resetBot() {
    std::vector<unsigned> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    GameField newField = GameField(10, 10);
    ShipManager newShips(shipSizes);
    this->enemy = Enemy(newShips, newField);

    setShips(shipSizes, enemy);
}

void Game::resetGame() {
    resetBot();
    std::vector<unsigned> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    GameField newField = GameField(10, 10);
    ShipManager newShips(shipSizes);
    AbilityManager newAbilities;
    this->player = Player(newShips, newField, newAbilities);

    setShips(shipSizes, player);
}

void Game::isGameEnded() {
    if (!this->isPlayerWin && !this->isBotWin) {
        this->gameover = false;
        return;
    }

    std::cout << "Do you want to continue playing? y/n" << std::endl;
    std::string line;
    std::cin >> line;
    if (line == "n" || line == "N") {
        this->gameover = true;
        return;
    }

    if (this->isPlayerWin) {
        resetBot();
        this->isPlayerWin = false;
    }
    if (this->isBotWin) {
        resetGame(); 
        this->isBotWin = false;
    }
}

void Game::loadGame(const std::string& file) {
    try {
        this->gameState.loadGame(file);
    } catch (nlohmann::json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return;
    } catch (HashMismatchException& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
}

void Game::saveGame(const std::string& file) {
    this->gameState.saveGame(file);
} 