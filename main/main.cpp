#include "core/include/Combatant.h"

int main()
{
    Combatant player1("Dwight", 33, 33, 15);
    player1.printStatus();
    player1.applyDamage(10);
    player1.printStatus();
    player1.applyHealing(4);
    player1.printStatus();

    return 0;
}

