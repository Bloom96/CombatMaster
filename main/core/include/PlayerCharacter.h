#pragma once

#include "Combatant.h"

class PlayerCharacter : public Combatant{
    private:
        std::string characterClass;
        int level;
        int initiative;

    public:
        PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, std::string newCharacterClass, int newLevel, int newInitiative);
        void printStatus() const override;
        void takeTurn() override;
        void setHPToMax() override;
        ~PlayerCharacter() override
        {
            std::cout << name << " has been destroyed." << std::endl;
        }
};