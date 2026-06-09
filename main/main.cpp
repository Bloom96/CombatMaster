#include "core/include/Combatant.h"
#include "core/include/PlayerCharacter.h"
#include "core/include/Enemy.h"
#include <vector>
#include <memory>

void printAll(std::vector<Combatant*> combatants);
void runCombat(Combatant** playerturn, int count);
void buildParty();
void printRoster(const std::vector<Combatant*>& combatant);
void addCombatant(std::vector<Combatant*>& combatant);
void resetHP(Combatant*& combatant);

template <typename T>
void printAll(const std::vector<T>& container)
{
    for (const T& element : container)
    {
        std::cout << element << std::endl;
    }
}


int main()
{
    std::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    printAll(a);

    std::vector<std::string> b;
    b.push_back("Hello there\n");
    b.push_back("GENERAL KENOBI\n");
    printAll(b);

    return 0;
}



void takeAllTurn(std::vector<Combatant*> combatants)
{
    for(Combatant* c : combatants)
    {
        c->takeTurn();
    }
}


void runCombat(Combatant** playerturn, int count)
{
    for(int i = 0; i < count; i++)
    {
        playerturn[i]->takeTurn();
    }
}

void buildParty()
{
    int size_of_party = 3;
    
    std::string enemy_name = "";

    std::vector<std::unique_ptr<Combatant>> e;

    e.push_back(std::make_unique<Enemy>("Goblin", 10, 10, 12, 0.1));
    e.push_back(std::make_unique<PlayerCharacter>("Jim", 10, 12, 15, "Paladin", 1));

    e.at(0)->printStatus();
    e.at(1)->printStatus();
    
}


void printRoster(const std::vector<Combatant*>& combatant)
{
    for (Combatant* c : combatant)
    {
        c->printStatus();
    }
}

void addCombatant(std::vector<Combatant*>& combatant)
{
    combatant.push_back(new PlayerCharacter("Jim",15,16,12,"Warlock", 2));
}

void resetHP(Combatant*& combatant)
{
    combatant->setHPToMax();
}


