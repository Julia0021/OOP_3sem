#pragma once
#include <queue>
#include "abilities/double_damage.h"
#include "abilities/random_ship_attack.h"
#include "abilities/scanner.h"

class AbilityManager 
{
private:
    std::queue<Ability*> abil_queue;
    std::vector<Ability*> abilities;
public:
    AbilityManager();

    void useAbility(GameField& field);

    void addAbility();

    void addAbility(Ability* ability);

    bool queueIsEmpty();

    Ability& getAbility(int index);

    int getQueueSize();

    void clearQueue();
};