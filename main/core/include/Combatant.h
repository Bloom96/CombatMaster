#pragma once
#include <string>
#include <iostream>
#include "ActionType.h"

class Combatant{

    protected:
        std::string name;
        int currentHP;
        int maxHP;
        int armorClass;        
        int initiative;

    public:
        Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newInitiative);
        virtual void printStatus() const;
        virtual void takeTurn(ActionType action, Combatant* target = nullptr) = 0;
        virtual std::string getType() const = 0;

        void applyDamage(int amount);
        void applyHealing(int amount);
        void setInitiative(int value);


        int getInitiative() const;
        std::string getName() const;
        bool isAlive() const;

        virtual void setHPToMax() = 0;
        virtual ~Combatant() 
        {
            std::cout << "Combatant base destroyed." << std::endl;
        }
};