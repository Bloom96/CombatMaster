#pragma once
#include <string>
#include <iostream>

class Combatant{

    protected:
        std::string name;
        int currentHP;
        int maxHP;
        int armorClass;

    public:
        Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass);
        virtual void printStatus();
        void applyDamage(int amount);
        void applyHealing(int amount);
};