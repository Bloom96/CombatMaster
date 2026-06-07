#include "../include/Enemy.h"

Enemy::Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, float newChallangeRating)
    : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass), challangeRating(newChallangeRating)
{
    
}

void Enemy::printStatus()
{
    Combatant::printStatus();
    std::cout << "CR : " << challangeRating << std::endl;
}