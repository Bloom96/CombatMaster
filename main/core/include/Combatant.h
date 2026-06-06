#pragma once
#include <string>
#include <iostream>

struct Combatant{

    std::string name;
    int currentHP;
    int maxHP;
    int armorClass;

    Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass)
    {
        name = newName;
        currentHP = newCurrentHP;
        maxHP = newMaxHP;
        armorClass = newArmorClass;
    }

    void printStatus()
    {
        std::cout << name << " | HP: " << currentHP << "/" << maxHP << " | AC: " << armorClass << std::endl;
    }
};

