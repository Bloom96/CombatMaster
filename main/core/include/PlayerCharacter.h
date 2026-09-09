#pragma once

#include "Combatant.h"

class PlayerCharacter : public Combatant{
    private:
        std::string characterClass;
        int level;
        int deathSaveSuccesses = 0;
        int deathSaveFailures = 0;
        bool downed = false;

    public:
        PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, std::string newCharacterClass, int newLevel);
        void printStatus() const override;
        void takeTurn(ActionType action, Combatant* target = nullptr) override;
        void setHP(int value) override; 
        void onDeath() override;  
        void rollForDeathSaving();
        void resetDeathSaveCounters();
        void evaluateDeathSaving();
        

        std::string getType() const override;
        bool isDowned() const;

        ~PlayerCharacter() override
        {
            std::cout << name << " has been destroyed." << std::endl;
        }
};