#pragma once

#include "Combatant.h"

class PlayerCharacter : public Combatant{
    private:
        std::string characterClass;
        int level;
        int deathSaveSuccesses;
        int deathSaveFailures;
        bool downed;

    public:
        PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive, std::string newCharacterClass, int newLevel, int newDeathSaveSuccesses, int newDeathSaveFailures, bool newDowned);
        void printStatus() const override;
        void takeTurn(ActionType action, Combatant* target = nullptr) override;
        void setHP(int value) override; 
        void onDeath() override;  
        void rollForDeathSaving();
        void resetDeathSaveCounters();
        

        std::string getType() const override;
        bool isDowned() const;

        ~PlayerCharacter() override
        {
            std::cout << name << " has been destroyed." << std::endl;
        }
};