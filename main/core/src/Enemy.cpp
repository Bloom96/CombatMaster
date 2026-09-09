#include "../include/Enemy.h"
#include "../include/ActionType.h"

/**
 * Enemy (constructor)
 * -----------------------------------------------------------------
 * Description : Builds an Enemy by delegating the shared fields (name,
 *               HP, AC, damage, initiative, alive) up to the Combatant
 *               base constructor, then initializing the Enemy-specific
 *               challengeRating field via the member-initializer list.
 * Called functions : Combatant::Combatant (base ctor)
 * Output      : Constructs the object; no console output, returns nothing.
 */
Enemy::Enemy(std::string newName, int newCurrentHP, int newMaxHP, int newArmorClass, int newBaseDamage, int newInitiative, bool newAlive, float newchallengeRating)
    : Combatant(newName, newCurrentHP, newMaxHP, newArmorClass, newBaseDamage, newInitiative, newAlive), challengeRating(newchallengeRating)
{  
    // Empty body - all initialization already happened in the member-initializer list above.
}

/**
 * printStatus
 * -----------------------------------------------------------------
 * Description : Extends the base class's status printout with the
 *               Enemy-specific field (challenge rating).
 * Called functions : Combatant::printStatus() (base class version)
 * Output      : Writes two lines to standard output. Returns nothing.
 */
void Enemy::printStatus() const
{
    Combatant::printStatus();                      // Print the shared fields (name, HP, AC) first.
    std::cout << "CR : " << challengeRating << std::endl;   // Then the Enemy-only field.
}

/**
 * takeTurn
 * -----------------------------------------------------------------
 * Description : Resolves this Enemy's turn: attacks the given target,
 *               or does nothing, depending on the action passed in.
 *               Assumes the caller (loopThroughCombat) only invokes
 *               this on a combatant that is still alive - death is
 *               detected immediately in Combatant::applyDamage(), not
 *               here.
 * Called functions : actionToString(), Combatant::applyDamage(),
 *                     Combatant::getCurrentHP(), Combatant::getMaxHP(),
 *                     Combatant::getName()
 * Output      : Console output describing the turn's outcome; may
 *               mutate target's HP via applyDamage(). Returns nothing.
 */
void Enemy::takeTurn(ActionType action, Combatant* target)
{
    if((nullptr != target)&&(ActionType::ACT == action))
    {
        std::cout << "The enemy character " << name << " made the action: " << actionToString(action) <<", against the target: " << target->getName() << std::endl;
        target->applyDamage(baseDamage);   // Deal this Enemy's base damage to the target; may trigger target's onDeath() internally.
        std::cout << "Target now has " << target->getCurrentHP() << " out of " << target->getMaxHP() << std::endl;
    }
    else if((nullptr == target)&&(ActionType::ACT != action))
    {
        std::cout << "Enemy decided to not do anything, moving on to the next combatant" << std::endl;
    }
    else
    {
        std::cout << "Invalid action" << std::endl;   // Mismatched target/action combination.
    }
}

/**
 * setHP
 * -----------------------------------------------------------------
 * Description : Directly overwrites currentHP with the given value.
 *               Required override to satisfy Combatant's pure virtual
 *               setHP(int) interface.
 * Called functions : (none)
 * Output      : Mutates currentHP. Returns nothing.
 *
 * NOTE: not called from anywhere in the code seen so far in this
 * conversation. That's expected/fine here, unlike a genuinely unused
 * helper - this override exists to satisfy the abstract base class
 * contract (Combatant::setHP is pure virtual), so Enemy must provide
 * it whether or not anything currently invokes it on this subclass.
 */
void Enemy::setHP(int value)
{
    currentHP = value;
}

/**
 * getType
 * -----------------------------------------------------------------
 * Description : Identifies this combatant's concrete type as a string,
 *               used throughout the codebase (loopThroughCombat, target
 *               filtering, alive-counter bookkeeping) to distinguish
 *               Enemies from PlayerCharacters without needing RTTI.
 * Called functions : (none)
 * Output      : Returns "Enemy".
 */
std::string Enemy::getType() const
{
    return "Enemy";
}

/**
 * onDeath
 * -----------------------------------------------------------------
 * Description : Called (via Combatant::applyDamage()) the instant this
 *               Enemy's HP reaches 0. Enemies die immediately and
 *               unconditionally - no downed state, no death saves.
 * Called functions : Combatant::setAlive()
 * Output      : Mutates alive to false. Returns nothing.
 */
void Enemy::onDeath()
{
    setAlive(false);
}