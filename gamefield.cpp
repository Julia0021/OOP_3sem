#include "gamefield.h"
#include "field_exceptions.h"

GameField::GameField(unsigned width, unsigned height) :width(width),height(height) {
    field.resize(height, std::vector<Cell>(width));
}

int GameField::getWidth() const {
    return width;
}

int GameField::getHeight() const {
    return height;
}

std::vector<std::vector<GameField::Cell>> GameField::getField() const {
    return field;
}

GameField::Cell& GameField::getCell(int x, int y) {
    return field[y][x];
}

void GameField::setShip(Ship* ship, int x, int y, bool isHorizontal) {

    // Проверка пересечения с другими кораблями
    for (int i = 0; i < ship->getLength(); i++) {
        int currentX = x + (isHorizontal ? i : 0);
        int currentY = y + (isHorizontal ? 0 : i);
        if (currentX < 0 || currentX >= width || currentY < 0 || currentY >= height) {
            throw ShipOutsideTheFieldException();
        }
        if (field[currentY][currentX].getStatus() == Cell::CellStatus::occupied) {
            throw ShipsClosePlacementException();
        }

        if (isHorizontal) {
            if ((currentY + 1 < height) && (field[currentY + 1][currentX].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
            if ((currentY - 1 >= 0) && (field[currentY - 1][currentX].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();

            if (i == 0) {
                if (currentX - 1 >= 0) {
                    if ((currentY + 1 < height) && (field[currentY + 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                    if (field[currentY][currentX - 1].getStatus() == Cell::CellStatus::occupied) throw ShipsClosePlacementException();
                    if ((currentY - 1 >= 0) && (field[currentY - 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                }
            }

            if (i + 1 == ship->getLength()) {
                if (currentX + 1 < width) {
                    if ((currentY + 1 < height) && (field[currentY + 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                    if (field[currentY][currentX + 1].getStatus() == Cell::CellStatus::occupied) throw ShipsClosePlacementException();
                    if ((currentY - 1 >= 0) && (field[currentY - 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                }
            }
        }

        if (!isHorizontal) {
            if ((currentX + 1 < width) && (field[currentY][currentX + 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
            if ((currentX - 1 >= 0) && (field[currentY][currentX - 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();

            if (i == 0) {
                if (currentY - 1 >= 0) {
                    if ((currentX + 1 < width) && (field[currentY - 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                    if (field[currentY - 1][currentX].getStatus() == Cell::CellStatus::occupied) throw ShipsClosePlacementException();
                    if ((currentX - 1 >= 0) && (field[currentY - 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                }
            }

            if (i + 1 == ship->getLength()) {
                if (currentY + 1 < height) {
                    if ((currentX + 1 < width) && (field[currentY + 1][currentX + 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                    if (field[currentY + 1][currentX].getStatus() == Cell::CellStatus::occupied) throw ShipsClosePlacementException();
                    if ((currentX - 1 >= 0) && (field[currentY + 1][currentX - 1].getStatus() == Cell::CellStatus::occupied)) throw ShipsClosePlacementException();
                }
            }
        }
    }

    // Установка корабля на поле
    for (int i = 0; i < ship->getLength(); i++) {
        int currentX = x + (isHorizontal ? i : 0);
        int currentY = y + (isHorizontal ? 0 : i);
        field[currentY][currentX].setStatus(Cell::CellStatus::occupied);
        field[currentY][currentX].setShip(ship);
        field[currentY][currentX].setShipSegIndex(i);
        field[currentY][currentX].setShipIndex(ship->index);
    }

    if (!isHorizontal) ship->changePosition();
}

bool GameField::attack(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw AttackOutsideTheFieldException();
    }

    Cell& cell = field[y][x];
    if (cell.getStatus() == Cell::CellStatus::occupied) {
        Ship* ship = cell.getShip();
        int index = cell.getShipSegIndex();
        ship->getSegDamaged(index);
        return true;
    } else {cell.setStatus(Cell::CellStatus::empty);}

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

void GameField::getOccupiedCellsCoords(std::vector<Coords>& coords_vec) {
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            if(this->isCellOccupied(x, y)) {
                Coords coords = {x, y};
                coords_vec.push_back(coords);
            }
        }
    }
}

void GameField::getNotDestroyedCellsCoords(std::vector<Coords>& coords_vec) {
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            if(this->isCellOccupied(x, y)) {
                int index = field[y][x].getShipSegIndex();
                if(field[y][x].getShip()->getSegStatus(index) != Ship::Segment::Destroyed) {
                    Coords coords = {x, y};
                    coords_vec.push_back(coords);
                }
            }  else if(this->getCell(x, y).getStatus() == Cell::CellStatus::unknown) {
                Coords coords = {x, y};
                coords_vec.push_back(coords);
            }
        }
    }
}

void GameField::getDamagedCellsCoords(std::vector<Coords>& coords_vec) {
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            if(this->isCellOccupied(x, y)) {
                int index = field[y][x].getShipSegIndex();
                if(field[y][x].getShip()->getSegStatus(index) == Ship::Segment::Damaged) {
                    Coords coords = {x, y};
                    coords_vec.push_back(coords);
                }
            }
        }
    }
}

void GameField::printField(bool hidden) {
    std::cout << "\n" << "  \033[4m ";
    for (int i = 0; i < width; i++) {
        std::cout << i;
        if (i != width - 1) std::cout << " ";
    }
    std::cout << "\033[24m " << "\n";

    for (int i = 0; i < height; i++) {
        std::cout << i << "| ";
        for (int j = 0; j < width; j++) {
            if(field[i][j].getStatus() == Cell::CellStatus::empty) std::cout << "\033[1;31m.\033[0m ";
            if(field[i][j].getStatus() == Cell::CellStatus::occupied) {
                int index = field[i][j].getShipSegIndex();
                if(this->getCell(j, i).getShip()->getSegStatus(index) == Ship::Segment::Destroyed) std::cout << "\033[1;31mX\033[0m ";
                if(this->getCell(j, i).getShip()->getSegStatus(index) == Ship::Segment::Intact) {
                    if(hidden) {
                        std::cout << "~ ";
                    } else {
                        std::cout << "\033[1;32mX\033[0m ";
                    }
                }
                if(this->getCell(j, i).getShip()->getSegStatus(index) == Ship::Segment::Damaged) std::cout << "\033[1;33mX\033[0m ";
            }
            if(field[i][j].getStatus() == Cell::CellStatus::unknown) std::cout << "~ ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}