#include "../include/Combatant.h" 

Combatant::Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newInitiative)
{
    name = newName;
    currentHP = newCurrentHP;
    maxHP = newMaxHP;
    armorClass = newArmorClass;
    initiative = newInitiative;
}

void Combatant::printStatus() const
{
    std::cout << name << " | HP: " << currentHP << "/" << maxHP << " | AC: " << armorClass << std::endl;
}

void Combatant::applyDamage(int amount)
{
    if (0 < currentHP)
    {
        if (amount > currentHP)
        {
            currentHP = 0;
        }
        else
        {
            currentHP -= amount;
        }
    }
}

void Combatant::applyHealing(int amount)
{
    if ((amount + currentHP) > maxHP)
    {
        currentHP = maxHP;
    }
    else
    {
        currentHP += amount;
    }
}

void Combatant::setInitiative(int value)
{
    initiative = value;
}

int Combatant::getInitiative() const
{
    return initiative;
}