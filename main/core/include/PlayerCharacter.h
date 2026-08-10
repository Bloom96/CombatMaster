#pragma once

#include "Combatant.h"

class PlayerCharacter : public Combatant{
    private:
        std::string characterClass;
        int level;

    public:
        PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newInitiative, std::string newCharacterClass, int newLevel);
        void printStatus() const override;
        void takeTurn(ActionType action, Combatant* target = nullptr) override;
        void setHPToMax() override;       
        std::string getType() const override;


        ~PlayerCharacter() override
        {
            std::cout << name << " has been destroyed." << std::endl;
        }
};