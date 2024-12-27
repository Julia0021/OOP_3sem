#pragma once
#include "base_ability.h"

class DoubleDamage : public Ability {
public:
    void apply(GameField& field) const override;
    std::string getName() const override;
};