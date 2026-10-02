#include "core/include/Combatant.h"
#include "core/include/PlayerCharacter.h"
#include "core/include/Enemy.h"
#include "core/include/StatTracker.h"
#include "core/include/ActionType.h"
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <QApplication>
#include "ui/MainWindow.h"

// ---------------------------------------------------------------------
// Forward declarations.
// NOTE: runCombat, buildParty, and printRoster are declared here but have
// no definition anywhere in this file - unimplemented placeholders for
// future work, not currently callable.
// ---------------------------------------------------------------------
void runCombat(Combatant** playerturn, int count);
void buildParty();
void printRoster(const std::vector<Combatant*>& combatant);
void addCombatant(std::vector<std::unique_ptr<Combatant>>& combatant);
void resetHP(Combatant*& combatant);

void loopThroughCombat(std::vector<std::unique_ptr<Combatant>>& combatant);

/**
 * printAll (generic template)
 * -----------------------------------------------------------------
 * Description : Prints every element of a vector, one per line, using
 *               operator<<. Works for any type T that has a valid
 *               std::ostream << T overload (e.g. int, std::string).
 * Called functions : std::cout::operator<< (via the stream)
 * Output      : Writes each element to standard output, one per line.
 *               Returns nothing.
 */
template <typename cica>
void printAll(const std::vector<cica>& var)
{
    // Iterate over every element by const reference (no copies made).
    for(const cica& cuki : var)
    {
        // Stream the element directly - relies on operator<< existing for type cica.
        std::cout<< cuki << std::endl;
    }
}

/**
 * printAll<Combatant*> (explicit specialization)
 * -----------------------------------------------------------------
 * Description : Specialized version of printAll for raw Combatant*
 *               pointers. Combatant has no operator<<, so instead of
 *               streaming the pointer itself, this calls each object's
 *               own printStatus() to display its state.
 * Called functions : Combatant::printStatus() (virtual - polymorphic,
 *                     runs whichever derived class's own status display)
 * Output      : Writes each combatant's status block to standard output.
 *               Returns nothing.
 */
template <>
void printAll<Combatant*>(const std::vector<Combatant*>& var)
{
    // Iterate over every raw pointer in the vector.
    for(const Combatant* enemy : var)
    {
        // Polymorphic call: prints whichever subclass (PlayerCharacter or
        // Enemy) this pointer actually points to.
        enemy->printStatus();
    }
}

/**
 * addCombatants (generic factory helper - currently unimplemented)
 * -----------------------------------------------------------------
 * Description : Template placeholder intended to prompt the user with
 *               promptmsg and construct/add a new combatant of type T
 *               into combatants, using the supplied creator callable.
 *               NOTE: the body is currently empty - no logic implemented.
 * Called functions : (none yet - placeholder)
 * Output      : (none yet - placeholder)
 */
template <typename T, typename Creator>
void addCombatants(std::vector<std::unique_ptr<Combatant>>& combatants, std::string promptmsg, Creator creator)
{

}

// Running counts of alive players/enemies. Used by loopThroughCombat()'s
// outer while-condition to detect when the encounter should end (one side
// wiped out). File-scope (static) mutable state, shared by every function
// below that touches combat.
static int alivePlayers = 0;
static int aliveEnemies = 0;


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

/**
 * addCombatant
 * -----------------------------------------------------------------
 * Description : Adds one hardcoded PlayerCharacter ("Jim") to the given
 *               roster. Appears to be a quick test/debug helper rather
 *               than a general-purpose add function - name and stats are
 *               fixed, not parameterized or user-driven.
 * Called functions : PlayerCharacter::PlayerCharacter (ctor)
 * Output      : Prints a confirmation line to standard output; mutates
 *               combatant by appending the new character. Returns nothing.
 */
void addCombatant(std::vector<std::unique_ptr<Combatant>>& combatant)
{
    // Construct and append a fixed test character: name "Jim", HP 15/16, AC 12,
    // 0 base damage, class "Warlock", level 2.
    combatant.push_back(std::make_unique<PlayerCharacter>("Jim",15,16,12,10,"Warlock",2));
    std::cout<< "JIM IS HERE" << std::endl;   // Debug/confirmation message.
}

/**
 * resetHP
 * -----------------------------------------------------------------
 * Description : Restores a single combatant's current HP back to their
 *               maximum, via a polymorphic call resolved by whichever
 *               subclass the pointer actually points to.
 * Called functions : Combatant::setHPToMax() (virtual)
 * Output      : Mutates the referenced combatant in place. Returns nothing.
 * NOTE : this calls setHPToMax(), which does not match the setHP(int)
 *        signature used elsewhere in the Combatant/Enemy/PlayerCharacter
 *        headers in this project - flagging in case this file is out of
 *        sync with the latest class interface.
 */
void resetHP(Combatant*& combatant)
{
    combatant->setHPToMax();   // Sets currentHP = maxHP on whichever subclass this pointer refers to.
}

/**
 * loopThroughCombat
 * -----------------------------------------------------------------
 * Description : Runs the entire turn-based combat encounter. Repeatedly
 *               iterates over the roster in initiative order; each alive
 *               combatant is prompted for an action (Attack / Skip / End
 *               encounter). Combatants that have died - whether already
 *               dead entering an iteration, an attack target that just
 *               died, or the acting combatant itself dying as a side
 *               effect of its own turn (e.g. a downed PlayerCharacter
 *               failing a death save) - are removed from the roster
 *               immediately rather than waiting for a later pass. The
 *               outer while loop repeats full passes over the roster
 *               until one side is wiped out or the user ends the
 *               encounter.
 * Called functions : Combatant::isAlive(), Combatant::getType(),
 *                     Combatant::takeTurn() (virtual), Combatant::getName(),
 *                     std::find_if, std::distance, std::stoi, std::getline
 * Output      : Extensive interactive console I/O (prompts, target lists,
 *               turn results). Mutates combatant (erases dead entries)
 *               and the file-scope alivePlayers/aliveEnemies counters.
 *               Returns nothing; ends when the loop's exit conditions
 *               are met.
 */
void loopThroughCombat(std::vector<std::unique_ptr<Combatant>>& combatant)
{
    int input;
    bool encounterOngoing = true;
    ActionType action_selected = ActionType::NONE;

    // Outer loop: keep running full passes over the roster as long as both
    // sides still have someone alive and the user hasn't ended the encounter.
    while ((alivePlayers > 0) && (aliveEnemies > 0) && (true == encounterOngoing))
    {
        // Inner loop: one pass through the roster in initiative order.
        // Index-based (not range-based) because elements get erased mid-loop;
        // note there is no increment in the for-header - "i" is advanced
        // manually at the bottom, only when no erase happened at that index.
        for (size_t i = 0; i < combatant.size() && true == encounterOngoing; /* no increment here */)
        {
            // --- Top-of-iteration cleanup ---
            // Catches anyone who died earlier and hasn't been removed yet
            // (e.g. still sitting dead from before this pass started).
            if (!combatant[i]->isAlive())
            {
                // Decrement whichever side's counter this combatant belonged to,
                // clamped at 0 so it can never go negative.
                if ("Player" == combatant[i]->getType())
                {
                    alivePlayers = std::max(0, alivePlayers - 1);
                }
                else if ("Enemy" == combatant[i]->getType())
                {
                    aliveEnemies = std::max(0, aliveEnemies - 1);
                }
                // Remove them from the roster. Deliberately no i++ here:
                // erasing shifts the next element down into index i, so
                // leaving i unchanged means the loop naturally visits it next.
                combatant.erase(combatant.begin() + i);
            }
            else
            {
                // --- Combatant[i] is alive: prompt for their action ---
                std::cout << "Choose your action, by typing its' number: \n1: Attack \n2: Skip \n3: End encounter \n";
                std::string menu_choice;
                std::getline(std::cin, menu_choice);
                input = std::stoi(menu_choice);                       // Parse the typed number.
                action_selected = static_cast<ActionType>(input);     // Map it onto the ActionType enum.
                
                if(ActionType::ACT == action_selected)
                {
                    // List valid targets: enemies if the actor is a Player, players if the actor is an Enemy.
                    std::cout << "Select your target from the list by typing it's name";
                    if (combatant[i]->getType() == "Player")
                    {
                        for (const std::unique_ptr<Combatant>& ele : combatant)
                        {
                            if (ele->getType() == "Enemy")
                            {
                                std::cout << ele->getName() << std::endl;
                            }
                        }
                    }
                    else
                    {
                        for (const std::unique_ptr<Combatant>& ele : combatant)
                        {
                            if (ele->getType() == "Player")
                            {
                                std::cout << ele->getName() << std::endl;
                            }
                        }                       
                    }
                    std::string target;
                    std::getline(std::cin, target);        // Read the target's typed name.

                    // Find the target by name. Returns combatant.end() if no match.
                    auto it = std::find_if(combatant.begin(), combatant.end(),
                    [&target](const std::unique_ptr<Combatant>& ele)
                    {
                        return ele->getName() == target;
                    });
                    if (it != combatant.end())
                    {
                        // Convert the iterator to a plain index before doing anything
                        // that might erase from the vector - erasing invalidates
                        // iterators, but a numeric index stays valid to reuse.
                        size_t targetIndex = static_cast<size_t>(std::distance(combatant.begin(), it));

                        // Resolve the attack: may reduce the target's HP to 0 and
                        // trigger its onDeath() internally (via applyDamage()).
                        combatant[i]->takeTurn(action_selected, combatant[targetIndex].get());

                        // Did the attack just kill the target? If so, remove them now
                        // rather than waiting for the loop to reach their index later.
                        if (false == combatant[targetIndex]->isAlive())
                        {
                            if ("Player" == combatant[targetIndex]->getType())
                            {
                                alivePlayers = std::max(0, alivePlayers - 1);
                            }
                            else if ("Enemy" == combatant[targetIndex]->getType())
                            {
                                aliveEnemies = std::max(0, aliveEnemies - 1);
                            }
                            combatant.erase(combatant.begin() + targetIndex);

                            // If the erased target was positioned before the current
                            // actor (i), everything from that point shifted left by
                            // one - so i must be decremented to keep pointing at the
                            // same actor for the rest of this iteration.
                            if (targetIndex < i)
                            {
                                i--;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Invalid target name. Turn skipped.\n";   // No match found; attacker's turn is wasted.
                    }
                }
                else if(ActionType::SKIP == action_selected)
                {
                    // No target needed; just runs the "do nothing" branch of takeTurn().
                    combatant[i]->takeTurn(action_selected);
                }
                else
                {
                    // Any other input value ends the encounter immediately;
                    // combatant[i] never actually takes a turn in this branch.
                    encounterOngoing = false;
                }

                // --- Post-turn self-check ---
                // Covers the case where the acting combatant itself died as a
                // side effect of its own turn - e.g. a downed PlayerCharacter
                // failing its 3rd death save inside takeTurn(). Bounds-checked
                // with (i < combatant.size()) in case an earlier erase in this
                // same iteration already shrank the vector past i.
                if ((i < combatant.size()) && (false == combatant[i]->isAlive()))
                {
                    if ("Player" == combatant[i]->getType())
                    {
                        alivePlayers = std::max(0, alivePlayers - 1);
                    }
                    else if ("Enemy" == combatant[i]->getType())
                    {
                        aliveEnemies = std::max(0, aliveEnemies - 1);
                    }
                    combatant.erase(combatant.begin() + i);
                    // No i++ here either - same reasoning as the top-of-loop erase:
                    // the next combatant has slid into index i.
                }
                else
                {
                    // Combatant[i] survived its turn (or never got one, in the
                    // End Encounter branch) - advance to the next roster position.
                    i++;
                }
            }
        }
    }
}