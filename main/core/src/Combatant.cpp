#include "../include/Combatant.h" 
#include <algorithm>

/**
 * Combatant (constructor)
 * -----------------------------------------------------------------
 * Description : Base-class constructor. Initializes every field shared
 *               by all combatant types (name, HP, AC, base damage,
 *               initiative, alive flag) via the member-initializer list.
 *               Called by every derived class's constructor (Enemy,
 *               PlayerCharacter) to set up the common portion of state.
 * Called functions : (none)
 * Output      : Constructs the object; no console output, returns nothing.
 */
Combatant::Combatant(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive)
    : name(newName), currentHP(newCurrentHP), maxHP(newMaxHP), armorClass(newArmorClass), baseDamage(newBaseDamage), initiative(newInitiative), alive(newAlive)
{
    // Empty body - all initialization already happened in the member-initializer list above.
}

/**
 * printStatus
 * -----------------------------------------------------------------
 * Description : Prints the fields common to every combatant (name,
 *               current/max HP, AC). Declared virtual so derived classes
 *               can extend it (Enemy and PlayerCharacter both call this
 *               base version first, then print their own extra fields).
 * Called functions : (none)
 * Output      : Writes one line to standard output. Returns nothing.
 */
void Combatant::printStatus() const
{
    std::cout << name << " | HP: " << currentHP << "/" << maxHP << " | AC: " << armorClass << std::endl;
}

/**
 * applyDamage
 * -----------------------------------------------------------------
 * Description : Applies incoming damage to this combatant, clamping the
 *               damage amount at 0 (no negative/healing-via-damage) and
 *               currentHP at 0 (no negative HP). The instant HP reaches
 *               exactly 0, immediately triggers the death hand-off via
 *               onDeath() - a pure virtual, so this polymorphically
 *               resolves to Enemy::onDeath() (dies outright) or
 *               PlayerCharacter::onDeath() (goes downed) depending on
 *               the concrete type. This is the single, centralized point
 *               where death is detected for every combatant type.
 * Called functions : onDeath() (virtual - resolves per subclass)
 * Output      : Mutates currentHP; may trigger further state changes via
 *               onDeath(). Returns nothing.
 */
void Combatant::applyDamage(int amount)
{
    amount = std::max(0, amount);                      // Reject negative "damage" (would otherwise heal).
    currentHP = std::max(0, currentHP - amount);        // Apply damage, floored at 0.
    if(0 == currentHP)
    {
        onDeath();      // Fires exactly once, the moment HP first reaches 0.
    }
}

/**
 * applyHealing
 * -----------------------------------------------------------------
 * Description : Restores HP to this combatant, clamping the heal amount
 *               at 0 (no negative healing) and currentHP at maxHP (no
 *               overheal beyond the combatant's maximum).
 * Called functions : (none)
 * Output      : Mutates currentHP. Returns nothing.
 *
 * NOTE - NOT CURRENTLY CALLED: no caller for this function has appeared
 * anywhere in the project files reviewed so far (main.cpp, Enemy.cpp,
 * PlayerCharacter.cpp). Not a bug - there's no Heal ActionType wired up
 * yet in the combat loop, so this is presumably staged for a future
 * feature rather than dead weight to remove.
 */
void Combatant::applyHealing(int amount)
{
    amount = std::max(0, amount);
    currentHP = std::min(maxHP, currentHP + amount);
}

/**
 * setInitiative
 * -----------------------------------------------------------------
 * Description : Overwrites this combatant's initiative value.
 * Called functions : (none)
 * Output      : Mutates initiative. Returns nothing.
 *
 * NOTE - NOT CURRENTLY CALLED: no caller has appeared anywhere in the
 * project files reviewed so far; combatants currently get their
 * initiative only via the constructor, and main.cpp sorts by
 * getInitiative() without ever calling this setter. Possibly intended
 * for a future re-roll-initiative feature.
 */
void Combatant::setInitiative(int value)
{
    initiative = value;
}

/**
 * getInitiative
 * -----------------------------------------------------------------
 * Description : Returns this combatant's initiative value, used by
 *               main() to sort the roster into turn order.
 * Called functions : (none)
 * Output      : Returns initiative.
 */
int Combatant::getInitiative() const
{
    return initiative;
}

/**
 * isAlive
 * -----------------------------------------------------------------
 * Description : Reports whether this combatant is still alive, per the
 *               alive flag (set false by onDeath() for an Enemy, or by
 *               evaluateDeathSaving() for a PlayerCharacter that fails
 *               3 death saves). This is the single source of truth used
 *               throughout the project (loopThroughCombat, takeTurn
 *               guards) to decide whether a combatant should still be
 *               acting or targetable.
 * Called functions : (none)
 * Output      : Returns alive.
 */
bool Combatant::isAlive() const
{
    return alive;
}

/**
 * getName
 * -----------------------------------------------------------------
 * Description : Returns this combatant's display name.
 * Called functions : (none)
 * Output      : Returns name.
 */
std::string Combatant::getName() const
{
    return name;
}

/**
 * getBaseDamage
 * -----------------------------------------------------------------
 * Description : Returns this combatant's base damage value.
 * Called functions : (none)
 * Output      : Returns baseDamage.
 *
 * NOTE - NOT CURRENTLY CALLED: baseDamage is protected, and both
 * Enemy::takeTurn() and PlayerCharacter::takeTurn() read the member
 * directly (target->applyDamage(baseDamage)) rather than going through
 * this getter. Not broken, just currently redundant with direct member
 * access from within the class hierarchy - this getter would only
 * matter to code outside the hierarchy (e.g. a future UI layer
 * displaying a combatant's stats) that only has a Combatant* to work with.
 */
int Combatant::getBaseDamage() const
{
    return baseDamage;
}

/**
 * getCurrentHP
 * -----------------------------------------------------------------
 * Description : Returns this combatant's current HP.
 * Called functions : (none)
 * Output      : Returns currentHP.
 */
int Combatant::getCurrentHP() const
{
    return currentHP;
}

/**
 * getMaxHP
 * -----------------------------------------------------------------
 * Description : Returns this combatant's maximum HP.
 * Called functions : (none)
 * Output      : Returns maxHP.
 */
int Combatant::getMaxHP() const
{
    return maxHP;
}


/**
 * setAlive
 * -----------------------------------------------------------------
 * Description : Overwrites this combatant's alive flag directly. Used
 *               by Enemy::onDeath() and PlayerCharacter::evaluateDeathSaving()
 *               to mark a combatant as dead.
 * Called functions : (none)
 * Output      : Mutates alive. Returns nothing.
 */
void Combatant::setAlive(bool value)
{
    alive = value;
}

/**
 * setHPToMax
 * -----------------------------------------------------------------
 * Description : Directly restores currentHP to maxHP, bypassing the
 *               per-subclass setHP(int) override.
 * Called functions : (none)
 * Output      : Mutates currentHP. Returns nothing.
 *
 * NOTE - worth double-checking: since setHP(int) exists as a virtual,
 * per-subclass-overridable mutator elsewhere in the hierarchy, this
 * function sets currentHP directly instead of calling setHP(maxHP).
 * That's harmless today since neither override does anything beyond
 * the plain assignment, but if a subclass's setHP() ever grows
 * additional side effects (e.g. clearing a downed flag), this function
 * would silently skip them since it writes to currentHP directly rather
 * than going through the virtual call. Worth confirming this is
 * intentional, or changing this to `setHP(maxHP);` for consistency.
 *
 * Also not currently called anywhere in main.cpp's actual execution
 * path - only resetHP() in main.cpp calls this, and resetHP() itself
 * doesn't appear to be invoked from main() yet.
 */
void Combatant::setHPToMax()
{
    setHP(maxHP);
}