#include "double_damage.h"
#include <limits>

void DoubleDamage::apply(GameField& field) const {
    int x, y;
    std::cout << "Please enter some coordinates to use the Double Damage ability.\n";
    std::cin >> x >> y;

    if (std::cin.fail()) {
        std::cerr << "Inappropriate input.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    field.attack(x, y);
    field.attack(x, y);
}

std::string DoubleDamage::getName() const { return "Double Damage"; };