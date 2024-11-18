#include "scanner.h"
#include <limits>

void Scanner::apply(GameField& field) const {
    int x, y;
    std::cout << "Please enter the coordinates of the left top cell to use the Scanner ability.\n";
    std::cin >> x >> y;

    if (std::cin.fail()) {
        std::cerr << "Inappropriate input.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if(field.isCellOccupied(x, y) or field.isCellOccupied(x+1, y) or field.isCellOccupied(x, y+1) or field.isCellOccupied(x+1, y+1)) {
        std::cout << "There is a ship segment in this area.\n";
        return;
    }

    std::cout << "There is no ship segment in this area.\n";
}