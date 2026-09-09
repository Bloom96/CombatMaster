#include "../include/Combatant.h" 
#include <algorithm>

Combatant::Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive)
    : name(newName), currentHP(newCurrentHP), maxHP(newMaxHP), armorClass(newArmorClass), baseDamage(newBaseDamage), initiative(newInitiative), alive(newAlive)
{
    
}

void Combatant::printStatus() const
{
    std::cout << name << " | HP: " << currentHP << "/" << maxHP << " | AC: " << armorClass << std::endl;
}

void Combatant::applyDamage(int amount)
{
    amount = std::max(0, amount);
    currentHP = std::max(0, currentHP - amount);
}

void Combatant::applyHealing(int amount)
{
    amount = std::max(0, amount);
    currentHP = std::min(maxHP, currentHP + amount);
}

void Combatant::setInitiative(int value)
{
    initiative = value;
}

int Combatant::getInitiative() const
{
    return initiative;
}

bool Combatant::isAlive() const
{
    return alive;
}

std::string Combatant::getName() const
{
    return name;
}

int Combatant::getBaseDamage() const
{
    return baseDamage;
}

int Combatant::getCurrentHP() const
{
    return currentHP;
}

int Combatant::getMaxHP() const
{
    return maxHP;
}

bool Combatant::isActive() const
{
    if(true == isAlive())
    {
        return true;
    }
    return false;
}

void Combatant::setAlive(bool value)
{
    alive = value;
}