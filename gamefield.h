#pragma once
#include <iostream>
#include <vector>
#include "ship.h"

class GameField 
{
private:
    class Cell {  
    public:
        enum class CellStatus {unknown, empty, occupied};

        Cell(Ship* ship = nullptr, CellStatus status = CellStatus::unknown) 
            :ship(ship),status(status) {};

        Ship* getShip() const { return ship; }
        CellStatus getStatus() const { return status; }
        unsigned getShipSegIndex() const { return shipSegIndex; }

        void setStatus(CellStatus newStatus) { status = newStatus; }
        void setShip(Ship* newShip) { ship = newShip; }
        void setShipSegIndex(unsigned index) { shipSegIndex = index; }

    private:
        Ship* ship;
        unsigned shipSegIndex;
        CellStatus status; 
    };

    unsigned width;
    unsigned height;
    std::vector<std::vector<Cell>> field;

public:
    GameField(unsigned width, unsigned height);

    // Конструктор копирования
    GameField(const GameField& other) : width(other.width), height(other.height) {
        field.resize(height, std::vector<Cell>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                field[i][j].setStatus(other.field[i][j].getStatus());
                if (other.field[i][j].getShip() != nullptr) {
                    field[i][j].setShip(new Ship(*other.field[i][j].getShip()));
                }
            }
        }
    }

    // Оператор присваивания копирования
    GameField& operator=(const GameField& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            field.resize(height, std::vector<Cell>(width));
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    field[i][j].setStatus(other.field[i][j].getStatus());
                    if (other.field[i][j].getShip() != nullptr) {
                        field[i][j].setShip(new Ship(*other.field[i][j].getShip()));
                    }
                }
            }
        }
        return *this;
    }

    // Конструктор перемещения
    GameField(GameField&& other) :width(other.width), height(other.height), field(std::move(other.field)) {
        other.width = 0;
        other.height = 0;
        other.field.clear();
    }

    // Оператор присваивания перемещения
    GameField& operator=(GameField&& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            field = std::move(other.field);
            other.width = 0;
            other.height = 0;
            other.field.clear();
        }
        return *this;
    }

    int getWidth() const;

    int getHeight() const;

    bool setShip(Ship* ship, int x, int y, bool isHorizontal);

    bool attack(int x, int y);

    bool isCellOccupied(int x, int y);
};