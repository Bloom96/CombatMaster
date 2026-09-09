#include "../include/PlayerCharacter.h"
#include "../include/ActionType.h"
#include <cstdlib>
#include <iostream>
#include <random>

#define CRITICAL_FAIL       1
#define CRITICAL_SUCCESS    20

#define COUNTER_REACHED     3

PlayerCharacter::PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive, std::string newCharacterClass, int newLevel, int newDeathSaveSuccesses, int newDeathSaveFailures, bool newDowned) 
        : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass, newBaseDamage, newInitiative, newAlive), characterClass(newCharacterClass), level(newLevel), deathSaveSuccesses(newDeathSaveSuccesses), deathSaveFailures(newDeathSaveFailures), downed(newDowned)
{

}


void PlayerCharacter::printStatus() const
{
    Combatant::printStatus();
    std::cout << "Class: " << characterClass << " | Level: " << level << std::endl; 
}

void PlayerCharacter::takeTurn(ActionType action, Combatant* target)
{
    if(currentHP == 0)
    {
        onDeath();
        return;
    }
    
    if((nullptr != target)&&(ActionType::ATTACK == action))
    {
        std::cout << "The player character " << name << " made the action: " << actionToString(action) <<", against the target: " << target->getName() << std::endl;
        target->applyDamage(baseDamage);
        std::cout << "Target now has " << target->getCurrentHP() << " out of " << target->getMaxHP() << std::endl;
    }
    else if((nullptr == target)&&(ActionType::ATTACK != action))
    {
        std::cout << "Player decided to not do anything, moving on to the next combatant" << std::endl;
    }
    else
    {
        std::cout << "Invalid action" << std::endl;
    }

}

void PlayerCharacter::setHP(int value)
{
    currentHP = value;
}

void PlayerCharacter::onDeath()
{
    if(false == downed)
    {
        downed = true;
    }
    rollForDeathSaving();
    if(COUNTER_REACHED <= deathSaveSuccesses)
    {
        downed = false;
        setHP(1);
        resetDeathSaveCounters();
    }
    else if(COUNTER_REACHED <= deathSaveFailures)
    {
        downed = false;
        setAlive(false);
        resetDeathSaveCounters();
    }

}

std::string PlayerCharacter::getType() const
{
    return "Player";
}

void PlayerCharacter::rollForDeathSaving()
{
    std::random_device rd;                          // seeds the generator
    std::mt19937 gen(rd());                          // Mersenne Twister engine
    std::uniform_int_distribution<> dist(1, 20);      // range [1, 20], inclusive
    int r = dist(gen);

    if(r <= 10)
    {
        if(CRITICAL_FAIL == r)
        {
            deathSaveFailures += 2;
        }
        else
        {
            deathSaveFailures++;
        }
        return;
    }
    else
    {
        if(CRITICAL_SUCCESS == r)
        {
            deathSaveSuccesses += 2;
        }
        else
        {
            deathSaveSuccesses++;
        }
    }

}

void PlayerCharacter::resetDeathSaveCounters()
{
    deathSaveFailures = deathSaveSuccesses = 0;
}