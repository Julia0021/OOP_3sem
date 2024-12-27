#include "random_ship_attack.h"
#include "../coordinates.h"
#include <algorithm>
#include <random>

void RandomAttack::apply(GameField& field) const {
    std::cout << "The Random Ship Attack ability now will be used.\n";

    std::vector<Coords> cells_coords;
    field.getOccupiedCellsCoords(cells_coords);

    if (cells_coords.empty()) {
        std::cout << "No occupied cells have been found.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cells_coords.begin(), cells_coords.end(), gen);

    auto firstPair = cells_coords.front();
    int randomX = firstPair.x;
    int randomY = firstPair.y;
    field.attack(randomX, randomY);
}

std::string RandomAttack::getName() const { return "Random Attack"; };