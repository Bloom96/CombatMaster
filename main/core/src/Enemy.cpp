#include "../include/Enemy.h"

Enemy::Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, float newchallengeRating, int newInitiative)
    : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass), challengeRating(newchallengeRating), initiative(newInitiative)
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

