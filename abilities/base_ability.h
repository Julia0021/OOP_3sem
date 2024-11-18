#pragma once
#include "../gamefield.h"

class Ability {
public:
    virtual ~Ability() = default;
    virtual void apply(GameField& field) const = 0;
};