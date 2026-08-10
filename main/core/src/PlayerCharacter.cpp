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

void PlayerCharacter::takeTurn(ActionType action, Combatant* target)
{
    std::string s;
    std::cout << name << " takes turn" << std::endl;
    std::cout << "What action does the player character take?" << std::endl;
    std::getline(std::cin, s);
    std::cout << "The player character called " << name << " took the action of " << s << std::endl;
}

void PlayerCharacter::setHPToMax()
{
    currentHP = maxHP;
}

std::string PlayerCharacter::getType() const
{
    return "Player";
}