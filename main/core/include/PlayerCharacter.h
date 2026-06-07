#pragma once

#include "Combatant.h"

class PlayerCharacter : public Combatant{
    private:
        std::string characterClass;
        int level;

    public:
        PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, std::string newCharacterClass, int newLevel);
        void printStatus() override;

};