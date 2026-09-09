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
        int baseDamage;     
        int initiative;
        bool alive = true;

    public:
        Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive);
        virtual void printStatus() const;
        virtual void takeTurn(ActionType action, Combatant* target = nullptr) = 0;
        virtual std::string getType() const = 0;

        void applyDamage(int amount);
        void applyHealing(int amount);
        void setInitiative(int value);
        void setAlive(bool value);
        void setHPToMax();

        int getInitiative() const;
        std::string getName() const;
        int getCurrentHP() const;
        int getMaxHP() const;
        bool isAlive() const;
        int getBaseDamage() const;

        virtual void onDeath() = 0;
        virtual void setHP(int value) = 0;
        virtual ~Combatant() 
        {
            std::cout << "Combatant base destroyed." << std::endl;
        }
};