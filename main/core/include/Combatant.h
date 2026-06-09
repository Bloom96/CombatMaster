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
        virtual void takeTurn() = 0;
        void applyDamage(int amount);
        void applyHealing(int amount);
        virtual void setHPToMax() = 0;
        virtual ~Combatant() 
        {
            std::cout << "Combatant base destroyed." << std::endl;
        }
};