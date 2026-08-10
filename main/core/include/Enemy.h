#pragma once

#include "Combatant.h"


class Enemy : public Combatant{

    private:
        float challengeRating;

    public:
        Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newInitiative, float newchallengeRating);
        void printStatus() const override;
        void takeTurn(ActionType action, Combatant* target = nullptr) override;
        void setHPToMax() override;
        std::string getType() const override;
        
        ~Enemy() override
        {
            std::cout << name << " has been destroyed." << std::endl;
        }
};