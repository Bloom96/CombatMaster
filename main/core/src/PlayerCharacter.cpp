#include "../include/PlayerCharacter.h"
#include "../include/ActionType.h"
#include <cstdlib>
#include <iostream>
#include <random>

#define CRITICAL_FAIL       1
#define CRITICAL_SUCCESS    20

#define COUNTER_REACHED     3

/**
 * PlayerCharacter (constructor)
 * -----------------------------------------------------------------
 * Description : Builds a PlayerCharacter by first delegating the shared
 *               fields (name, HP, AC, damage, initiative, alive) up to
 *               the Combatant base constructor, then initializing the
 *               PC-specific fields via the member-initializer list.
 * Called functions : Combatant::Combatant (base ctor)
 * Output      : Constructs the object; no console output, returns nothing.
 */
PlayerCharacter::PlayerCharacter(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive, std::string newCharacterClass, int newLevel, int newDeathSaveSuccesses, int newDeathSaveFailures, bool newDowned) 
        : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass, newBaseDamage, newInitiative, newAlive), characterClass(newCharacterClass), level(newLevel), deathSaveSuccesses(newDeathSaveSuccesses), deathSaveFailures(newDeathSaveFailures), downed(newDowned)
{
    // Empty body - all initialization already happened in the member-initializer list above.
}


/**
 * printStatus
 * -----------------------------------------------------------------
 * Description : Extends the base class's status printout with the
 *               PC-specific fields (class and level).
 * Called functions : Combatant::printStatus() (base class version)
 * Output      : Writes two lines to standard output. Returns nothing.
 */
void PlayerCharacter::printStatus() const
{
    Combatant::printStatus();      // Print the shared fields (name, HP, AC) first.
    std::cout << "Class: " << characterClass << " | Level: " << level << std::endl;   // Then the PC-only fields.
}

/**
 * takeTurn
 * -----------------------------------------------------------------
 * Description : Resolves this PlayerCharacter's turn. If downed, the
 *               turn is entirely replaced by a death-saving-throw
 *               resolution (no normal action taken). If dead, does
 *               nothing. Otherwise, attacks the given target or does
 *               nothing, depending on the action passed in.
 * Called functions : evaluateDeathSaving(), Combatant::isAlive(),
 *                     actionToString(), Combatant::applyDamage(),
 *                     Combatant::getCurrentHP(), Combatant::getMaxHP(),
 *                     Combatant::getName()
 * Output      : Console output describing the turn's outcome; may
 *               mutate target's HP via applyDamage(). Returns nothing.
 *
 * FLAG - LIKELY BUG: this function compares against ActionType::ACT,
 * but every other class in the project (Enemy::takeTurn, and the caller
 * in loopThroughCombat) uses ActionType::ATTACK for the same action.
 * If ACT and ATTACK are different enumerators, an actual ATTACK
 * selection passed in from the combat loop will never match either
 * branch below correctly, and this will silently fall into the "Invalid
 * action" branch instead of resolving the attack. This looks like a
 * typo (ATTACK -> ACT) rather than an intentional divergence - worth
 * double-checking ActionType.h and fixing to ATTACK for consistency.
 */
void PlayerCharacter::takeTurn(ActionType action, Combatant* target)
{
    if(true == downed)
    {
        // Downed PCs don't take a normal action; their "turn" is a death save instead.
        evaluateDeathSaving();
        return;
    }
    else if(false == isAlive())
    {
        // Already dead (shouldn't normally reach this point if the caller
        // removes dead combatants promptly, but guards against it anyway).
        return;
    }

    // FLAG: ActionType::ACT - see function-level note above; almost certainly
    // should be ActionType::ATTACK to match Enemy::takeTurn and the caller.
    if((nullptr != target)&&(ActionType::ACT == action))
    {
        std::cout << "The player character " << name << " made the action: " << actionToString(action) <<", against the target: " << target->getName() << std::endl;
        target->applyDamage(baseDamage);   // Deal this PC's base damage to the target; may trigger target's onDeath() internally.
        std::cout << "Target now has " << target->getCurrentHP() << " out of " << target->getMaxHP() << std::endl;
    }
    // FLAG: same ActionType::ACT concern as above.
    else if((nullptr == target)&&(ActionType::ACT != action))
    {
        std::cout << "Player decided to not do anything, moving on to the next combatant" << std::endl;
    }
    else
    {
        std::cout << "Invalid action" << std::endl;   // Mismatched target/action combination (e.g. target given with a non-attack action).
    }

}

/**
 * setHP
 * -----------------------------------------------------------------
 * Description : Directly overwrites currentHP with the given value,
 *               bypassing the max-HP clamp that applyHealing() enforces.
 *               Used specifically for the "stabilize at 1 HP" case in
 *               evaluateDeathSaving(), where an exact value is wanted
 *               rather than an additive heal.
 * Called functions : (none)
 * Output      : Mutates currentHP. Returns nothing.
 */
void PlayerCharacter::setHP(int value)
{
    currentHP = value;
}

/**
 * onDeath
 * -----------------------------------------------------------------
 * Description : Called (via Combatant::applyDamage()) the instant this
 *               PC's HP reaches 0. Performs only the immediate state
 *               transition - marks the PC as downed. Does NOT roll a
 *               death save; that only happens later, on the PC's own
 *               turn, via evaluateDeathSaving().
 * Called functions : (none)
 * Output      : Mutates downed. Returns nothing.
 */
void PlayerCharacter::onDeath()
{
    if(false == downed)
    {
        downed = true;
    }
    // Deliberately no roll here - see evaluateDeathSaving() for that logic.
    // Splitting these two concerns avoids double-rolling a save on the
    // same drop-to-0 event (once from the attacker's turn, once again
    // later on the PC's own turn).
}

/**
 * getType
 * -----------------------------------------------------------------
 * Description : Identifies this combatant's concrete type as a string,
 *               used throughout the codebase (loopThroughCombat, target
 *               filtering, alive-counter bookkeeping) to distinguish
 *               PlayerCharacters from Enemies without needing RTTI.
 * Called functions : (none)
 * Output      : Returns "Player".
 */
std::string PlayerCharacter::getType() const
{
    return "Player";
}

/**
 * rollForDeathSaving
 * -----------------------------------------------------------------
 * Description : Rolls one d20 death saving throw and updates the raw
 *               success/failure counters accordingly, following D&D 5e
 *               rules: 1-9 is a failure, 10-19 is a success, a natural 1
 *               counts as two failures, a natural 20 counts as two
 *               successes. Does not resolve/interpret the outcome (does
 *               not check for 3 reached, does not change downed/alive
 *               state) - that's evaluateDeathSaving()'s job.
 * Called functions : std::random_device, std::mt19937,
 *                     std::uniform_int_distribution
 * Output      : Mutates deathSaveFailures or deathSaveSuccesses. Returns nothing.
 */
void PlayerCharacter::rollForDeathSaving()
{
    std::random_device rd;                          // seeds the generator
    std::mt19937 gen(rd());                          // Mersenne Twister engine
    std::uniform_int_distribution<> dist(1, 20);      // range [1, 20], inclusive
    int r = dist(gen);

    if(r < 10)
    {
        // NOTE: this branch covers r == 10 as well as r <= 9. A roll of
        // exactly 10 is a success under standard 5e rules (10+ succeeds),
        // so this boundary is worth double-checking against the rules
        // you intend to implement - as written, a 10 counts as a failure.
        if(CRITICAL_FAIL == r)
        {
            deathSaveFailures += 2;    // Natural 1: counts as two failures.
        }
        else
        {
            deathSaveFailures++;
        }
        return;
    }
    else
    {
        if(CRITICAL_SUCCESS == r)
        {
            deathSaveSuccesses += 2;   // Natural 20: counts as two successes.
        }
        else
        {
            deathSaveSuccesses++;
        }
    }

}

/**
 * resetDeathSaveCounters
 * -----------------------------------------------------------------
 * Description : Zeroes both death-save counters. Called once a PC's
 *               death-save sequence resolves (either stabilized or
 *               died), so a future drop-to-0 event starts the count fresh.
 * Called functions : (none)
 * Output      : Mutates deathSaveFailures and deathSaveSuccesses. Returns nothing.
 */
void PlayerCharacter::resetDeathSaveCounters()
{
    deathSaveFailures = deathSaveSuccesses = 0;
}

/**
 * evaluateDeathSaving
 * -----------------------------------------------------------------
 * Description : Runs one full death-save turn for a downed PC: rolls a
 *               save, then checks whether the roll pushed either counter
 *               to the 3-reached threshold. On 3 successes, stabilizes
 *               the PC at 1 HP and clears downed. On 3 failures, kills
 *               the PC (setAlive(false)) and clears downed. If neither
 *               threshold is reached yet, the PC simply stays downed
 *               until their next turn.
 * Called functions : rollForDeathSaving(), setHP(), resetDeathSaveCounters(),
 *                     Combatant::setAlive()
 * Output      : Mutates downed, currentHP or alive, and the death-save
 *               counters. Returns nothing.
 */
void PlayerCharacter::evaluateDeathSaving()
{
    rollForDeathSaving();
    if(COUNTER_REACHED <= deathSaveSuccesses)
    {
        // 3+ successes: stabilize. HP is set to exactly 1 (not healed via
        // applyHealing, since that would also apply the max-HP clamp logic
        // unnecessarily for this fixed value).
        downed = false;
        setHP(1);
        resetDeathSaveCounters();
    }
    else if(COUNTER_REACHED <= deathSaveFailures)
    {
        // 3+ failures: the PC dies. Removal from the roster itself happens
        // in loopThroughCombat's post-turn check, not here.
        downed = false;
        setAlive(false);
        resetDeathSaveCounters();
    }
    // else: neither threshold reached yet - stays downed, no state change
    // beyond the counter increment already applied inside rollForDeathSaving().
}

// -----------------------------------------------------------------
// FLAG - MISSING IMPLEMENTATION: PlayerCharacter.h declares
//     bool isDowned() const;
// but no definition for it exists anywhere in this .cpp file. It's a
// plain (non-virtual) member function, so this won't fail to compile or
// link on its own - it will only break the moment something actually
// calls player->isDowned() (e.g. from loopThroughCombat to filter valid
// attack targets, or from a future UI layer). Worth adding a one-line
// definition now while it's fresh:
//
//     bool PlayerCharacter::isDowned() const
//     {
//         return downed;
//     }
// -----------------------------------------------------------------