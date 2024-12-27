#include "game.h"

int main() 
{
    Coords fieldSize = {10, 10}; 
    std::vector<unsigned> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    GameField player_field(fieldSize.y, fieldSize.x);
    GameField enemy_field(player_field);
    AbilityManager ability_manager;
    ShipManager player_ships(shipSizes);
    ShipManager enemy_ships(shipSizes);

    Player player = Player(player_ships, player_field, ability_manager);
    Enemy enemy = Enemy(enemy_ships, enemy_field);
    GameState gameState = GameState(player, enemy);
    Game game = Game(player, enemy, gameState, shipSizes);
    game.startGame();
  
    return 0;
}