#include "../include/Enemy.h"
#include "../include/ActionType.h"

Enemy::Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive, float newchallengeRating)
    : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass, newBaseDamage, newInitiative, newAlive), challengeRating(newchallengeRating)
{  
    
}

void Enemy::printStatus() const
{
    Combatant::printStatus();
    std::cout << "CR : " << challengeRating << std::endl;
}

void Enemy::takeTurn(ActionType action, Combatant* target)
{
    if(currentHP == 0)
    {
        onDeath();
        return;
    }
    if((nullptr != target)&&(ActionType::ATTACK == action))
    {
        std::cout << "The enemy character " << name << " made the action: " << actionToString(action) <<", against the target: " << target->getName() << std::endl;
        target->applyDamage(baseDamage);
        std::cout << "Target now has " << target->getCurrentHP() << " out of " << target->getMaxHP() << std::endl;
    }
    else if((nullptr == target)&&(ActionType::ATTACK != action))
    {
        std::cout << "Enemy decided to not do anything, moving on to the next combatant" << std::endl;
    }
    else
    {
        std::cout << "Invalid action" << std::endl;
    }
}

void Enemy::setHP(int value)
{
    currentHP = value;
}

std::string Enemy::getType() const
{
    return "Enemy";
}

void Enemy::onDeath()
{
    setAlive(false);
}