#pragma once

#include "Combatant.h"


class Enemy : public Combatant{

    private:
        float challengeRating;

    public:
        Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, float newchallengeRating);
        void printStatus() override;
        void takeTurn() override;
};