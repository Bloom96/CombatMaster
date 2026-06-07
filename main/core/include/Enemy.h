#pragma once

#include "Combatant.h"


class Enemy : public Combatant{

    private:
        float challangeRating;

    public:
        Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, float newChallangeRating);
        void printStatus() override;
};