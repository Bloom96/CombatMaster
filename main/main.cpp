#include "core/include/Combatant.h"
#include "core/include/PlayerCharacter.h"
#include "core/include/Enemy.h"
#include <vector>

void printAll(std::vector<Combatant*> combatants);


int main()
{
    std::vector<Combatant*> everyone;

    everyone.push_back(new Enemy("Dwight", 33, 35, 15, 0.5));
    everyone.push_back(new PlayerCharacter("Jim",15,22,10,"warlock",4));
    
    printAll(everyone);
    return 0;
}

void printAll(std::vector<Combatant*> combatants)
{
    for(Combatant* c : combatants)
    {
        c->printStatus();
    }
}


