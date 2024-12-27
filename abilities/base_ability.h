#pragma once
#include "../gamefield.h"

class Ability {
public:
    virtual ~Ability() = default;
    virtual void apply(GameField& field) const = 0;
    virtual std::string getName() const = 0;
};