#include "../include/PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newInitiative, std::string newCharacterClass, int newLevel) 
        : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass, newInitiative), characterClass(newCharacterClass), level(newLevel)
{

}

void PlayerCharacter::printStatus() const
{
    Combatant::printStatus();
    std::cout << "Class: " << characterClass << " | Level: " << level << std::endl; 
}

void PlayerCharacter::takeTurn()
{
    std::cout << name << " takes turn" << std::endl;
}

void PlayerCharacter::setHPToMax()
{
    currentHP = maxHP;
}