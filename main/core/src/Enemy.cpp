#include "../include/Enemy.h"

Enemy::Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newInitiative, float newchallengeRating)
    : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass, newInitiative), challengeRating(newchallengeRating)
{  
    
}

void Enemy::printStatus() const
{
    Combatant::printStatus();
    std::cout << "CR : " << challengeRating << std::endl;
}

void Enemy::takeTurn()
{
    std::cout << name << " takes turn" << std::endl;
}

void Enemy::setHPToMax()
{
    currentHP = maxHP;
}

