#include "core/include/Combatant.h"
#include "core/include/PlayerCharacter.h"
#include "core/include/Enemy.h"
#include "core/include/StatTracker.h"
#include <map>
#include <vector>
#include <memory>
#include <iostream>

//void printAll(std::vector<Combatant*> combatants);
void runCombat(Combatant** playerturn, int count);
void buildParty();
void printRoster(const std::vector<Combatant*>& combatant);
void addCombatant(std::vector<Combatant*>& combatant);
void resetHP(Combatant*& combatant);

template <typename cica>
void printAll(const std::vector<cica>& var)
{
    for(const cica& cuki : var)
    {
        std::cout<< cuki << std::endl;
    }
}

template <>
void printAll<Combatant*>(const std::vector<Combatant*>& var)
{
    for(const Combatant* enemy : var)
    {
        enemy->printStatus();
    }
}


int main()
{
    std::map<std::string, int> initiativeTracker;

    initiativeTracker["Jim"] = 10;
    initiativeTracker["Dwight"] = 15;
    initiativeTracker["Angela"] = 13;
    initiativeTracker["Karen"] = 2;

    initiativeTracker["Troll"] = 10;
    initiativeTracker["Goblin"] = 20;

    for(auto it = initiativeTracker.begin(); it != initiativeTracker.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    auto found = std::find_if(initiativeTracker.begin(), initiativeTracker.end(),
        [](const auto& a)
        {
            return a.second > 12;
        }
    );

    if (found != initiativeTracker.end())
    {
        std::cout << found->first << ": " << found->second << std::endl;
    }

    for( auto it =initiativeTracker.rbegin(); it != initiativeTracker.rend(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

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

    e.push_back(std::make_unique<Enemy>("Goblin", 10, 10, 12, 0.1,1));
    e.push_back(std::make_unique<PlayerCharacter>("Jim", 10, 12, 15, "Paladin", 1,1));

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
    combatant.push_back(new PlayerCharacter("Jim",15,16,12,"Warlock", 2,0));
}

void resetHP(Combatant*& combatant)
{
    combatant->setHPToMax();
}


