#include "gamefield.h"

GameField::GameField(unsigned width, unsigned height) :width(width),height(height) {
    field.resize(height, std::vector<Cell>(width));
}

int GameField::getWidth() const {
    return width;
}

int GameField::getHeight() const {
    return height;
}

bool GameField::setShip(Ship* ship, int x, int y, bool isHorizontal) {

    // Проверка пересечения с другими кораблями
    for (int i = 0; i < ship->getLength(); i++) {
        int currentX = x + (isHorizontal ? i : 0);
        int currentY = y + (isHorizontal ? 0 : i);
        if (currentX < 0 || currentX >= width || currentY < 0 || currentY >= height) {
            return false;
        }
        if (field[currentY][currentX].getStatus() == Cell::CellStatus::occupied) {
            return false;
        }

        if (isHorizontal) {
            if ((currentY + 1 < height) && (field[currentY + 1][currentX].getStatus() == Cell::CellStatus::occupied)) return false;
            if ((currentY - 1 >= 0) && (field[currentY - 1][currentX].getStatus() == Cell::CellStatus::occupied)) return false;

            if (i == 0) {
                if (currentX - 1 >= 0) {
                    if ((currentY + 1 < height) && (field[currentY + 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) return false;
                    if (field[currentY][currentX - 1].getStatus() == Cell::CellStatus::occupied) return false;
                    if ((currentY - 1 >= 0) && (field[currentY - 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) return false;
                }
            }

            if (i + 1 == ship->getLength()) {
                if (currentX + 1 < width) {
                    if ((currentY + 1 < height) && (field[currentY + 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) return false;
                    if (field[currentY][currentX + 1].getStatus() == Cell::CellStatus::occupied) return false;
                    if ((currentY - 1 >= 0) && (field[currentY - 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) return false;
                }
            }
        }

        if (!isHorizontal) {
            if ((currentX + 1 < width) && (field[currentY][currentX + 1].getStatus() == Cell::CellStatus::occupied)) return false;
            if ((currentX - 1 >= 0) && (field[currentY][currentX - 1].getStatus() == Cell::CellStatus::occupied)) return false;

            if (i == 0) {
                if (currentY - 1 >= 0) {
                    if ((currentX + 1 < width) && (field[currentY - 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) return false;
                    if (field[currentY - 1][currentX].getStatus() == Cell::CellStatus::occupied) return false;
                    if ((currentX - 1 >= 0) && (field[currentY - 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) return false;
                }
            }

            if (i + 1 == ship->getLength()) {
                if (currentY + 1 < height) {
                    if ((currentX + 1 < width) && (field[currentY + 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) return false;
                    if (field[currentY + 1][currentX].getStatus() == Cell::CellStatus::occupied) return false;
                    if ((currentX - 1 >= 0) && (field[currentY + 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) return false;
                }
            }
        }
    }

    // Установка корабля на поле
    for (int i = 0; i < ship->getLength(); i++) {
        int currentX = x + (isHorizontal ? 0 : i);
        int currentY = y + (isHorizontal ? i : 0);
        field[currentY][currentX].setStatus(Cell::CellStatus::occupied);
        field[currentY][currentX].setShip(ship);
        field[currentY][currentX].setShipSegIndex(i);
    }

    if (!isHorizontal) ship->changePosition();
    return true;
}

bool GameField::attack(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }

    Cell cell = field[y][x];
    if (cell.getStatus() == Cell::CellStatus::occupied) {
        Ship* ship = cell.getShip();
        ship->getSegDamaged(cell.getShipSegIndex());
        return true;
    }

    return false;
}

bool GameField::isCellOccupied(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }

    Cell cell = field[y][x];
    if (cell.getStatus() == Cell::CellStatus::occupied) return true;
    
    return false;
}