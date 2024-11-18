#include "ability_manager.h"
#include "ability_exception.h"
#include <algorithm>
#include <random>
#include <vector>

AbilityManager::AbilityManager() {
    this->abilities.push_back(new Scanner());
    this->abilities.push_back(new RandomAttack());
    this->abilities.push_back(new DoubleDamage());

    std::random_device rd;
    std::mt19937 g(rd()); 
    std::shuffle(abilities.begin(), abilities.end(), g);

    for (Ability* a : abilities) {
        this->abil_queue.push(a);
    }
}

void AbilityManager::useAbility(GameField& field) {
    if(this->abil_queue.empty()) throw EmptyAbilitiesException();

    this->abil_queue.front()->apply(field);
    this->abil_queue.pop();
}

void AbilityManager::addAbility() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, this->abilities.size()-1);

    this->abil_queue.push(this->abilities[distrib(gen)]);
}

bool AbilityManager::queueIsEmpty() {
    return this->abil_queue.empty();
}