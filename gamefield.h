#pragma once
#include <iostream>
#include <vector>
#include "ship.h"
#include "coordinates.h"

class GameField 
{
public:
    class Cell {  
    public:
        enum class CellStatus {unknown, empty, occupied};

        Cell(Ship* ship = nullptr, CellStatus status = CellStatus::unknown) 
            :ship(ship),status(status) {};

        Ship* getShip() const { return ship; }
        CellStatus getStatus() const { return status; }
        unsigned getShipSegIndex() const { return shipSegIndex; }
        int getShipIndex() const { return shipIndex; }

        void setStatus(CellStatus newStatus) { status = newStatus; }
        void setShip(Ship* newShip) { ship = newShip; }
        void setShipSegIndex(unsigned index) { shipSegIndex = index; }
        void setShipIndex(int index) { shipIndex = index; }

    private:
        Ship* ship;
        unsigned shipSegIndex;
        int shipIndex;
        CellStatus status; 
    };

    GameField() : height(0), width(0) {};
    GameField(unsigned width, unsigned height);

    // Конструктор копирования
    GameField(const GameField& other) : width(other.width), height(other.height) {
        field.resize(height, std::vector<Cell>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                field[i][j].setStatus(other.field[i][j].getStatus());
                field[i][j].setShipIndex(other.field[i][j].getShipIndex());
                field[i][j].setShipSegIndex(other.field[i][j].getShipSegIndex());
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
                    field[i][j].setShipIndex(other.field[i][j].getShipIndex());
                    field[i][j].setShipSegIndex(other.field[i][j].getShipSegIndex());
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

    std::vector<std::vector<Cell>> getField() const;

    Cell& getCell(int x, int y);

    void setShip(Ship* ship, int x, int y, bool isHorizontal);

    bool attack(int x, int y);

    bool isCellOccupied(int x, int y);

    void getOccupiedCellsCoords(std::vector<Coords>& coords);

    void getNotDestroyedCellsCoords(std::vector<Coords>& coords_vec);

    void getDamagedCellsCoords(std::vector<Coords>& coords_vec);

    void printField(bool hidden = false);

    bool anotherShipDestroyed();
    
private:
    unsigned width;
    unsigned height;
    std::vector<std::vector<Cell>> field;
};