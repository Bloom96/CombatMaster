#include "core/include/Combatant.h"

int main()
{
    Combatant player1("Dwight", 30, 33, 15);
    Combatant player2("Jim", 40, 44, 10);
    player1.printStatus();
    player2.printStatus();

    return 0;
}

