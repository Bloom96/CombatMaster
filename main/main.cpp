#include "core/include/Combatant.h"
#include "core/include/PlayerCharacter.h"
#include "core/include/Enemy.h"
#include "core/include/Pool.h"
#include <vector>
#include <memory>

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
    std::vector<int> count;

    std::vector<std::string> name;
    int all;

    Pool<int> hpPool;

    hpPool.add(100);
    hpPool.add(75);

    Pool<std::string> namePool;
    namePool.add("Aragorn");
    namePool.add("Legolas");

    printAll(hpPool.getAll());
    printAll(namePool.getAll());

    std::cout << hpPool.getCount() << std::endl;
    std::cout << namePool.getCount() << std::endl;
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


