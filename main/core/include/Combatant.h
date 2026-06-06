#pragma once
#include <string>
#include <iostream>

class Combatant{

    private:
        std::string name;
        int currentHP;
        int maxHP;
        int armorClass;

    public:
        Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass);
        void printStatus();
        void applyDamage(int amount);
        void applyHealing(int amount);
};