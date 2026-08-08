#include "core/include/Combatant.h"
#include "core/include/PlayerCharacter.h"
#include "core/include/Enemy.h"
#include "core/include/StatTracker.h"
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <algorithm>

void runCombat(Combatant** playerturn, int count);
void buildParty();
void printRoster(const std::vector<Combatant*>& combatant);
void addCombatant(std::vector<std::unique_ptr<Combatant>>& combatant);
void resetHP(Combatant*& combatant);

void loopThroughCombat(std::vector<std::unique_ptr<Combatant>>& combatant);

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

template <typename T, typename Creator>
void addCombatants(std::vector<std::unique_ptr<Combatant>>& combatants, std::string promptmsg, Creator creator)
{

}

static int alivePlayers = 0;
static int aliveEnemies = 0;

int main()
{
    int num_of_characters;
    int num_of_enemies;

    std::string character_name, playerinfo_class;
    std::vector<std::unique_ptr<Combatant>> Combatants;

    std::cout << "How many player characters to add?" << std::endl;
    std::cin >> num_of_characters;
    alivePlayers = num_of_characters;

    try
    {
        if (num_of_characters < 1)
        {        
            throw std::invalid_argument("Invalid number of player characters");
        }
        for(int i = 0; i < num_of_characters; i++)
        {
            std::cout << "Enter the name, and class of the player character: ";
            std::cin >> character_name >> playerinfo_class;
            Combatants.push_back(std::make_unique<PlayerCharacter>(character_name, 10, 10, 13, 12, playerinfo_class, 0));
            Combatants.back()->printStatus();
        }

    } 
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << "\n";
    }

    std::cout << "How many enemy characters to add?" << std::endl;
    std::cin >> num_of_enemies;
    aliveEnemies = num_of_enemies;

    try
    {
        if (num_of_enemies < 1)
        {        
            throw std::invalid_argument("Invalid number of enemy characters");
        }
        for(int i = 0; i < num_of_enemies; i++)
        {
            std::cout << "Enter a unique name for an enemy character: ";
            std::cin >> character_name;
            Combatants.push_back(std::make_unique<Enemy>(character_name,10, 10, 10, 10, 0.1));
            Combatants.back()->printStatus();
        }
    } 
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << "\n";
    }

    std::sort(Combatants.begin(), Combatants.end(), (
        [](const std::unique_ptr<Combatant>& a, const std::unique_ptr<Combatant>& b)
        {
            return a->getInitiative() > b->getInitiative();
        }
    ));
    
    std::cin.ignore();
    loopThroughCombat(Combatants);

    return 0;
}


void addCombatant(std::vector<std::unique_ptr<Combatant>>& combatant)
{
    combatant.push_back(std::make_unique<PlayerCharacter>("Jim",15,16,12,0,"Warlock",2));
    std::cout<< "JIM IS HERE" << std::endl;
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

void resetHP(Combatant*& combatant)
{
    combatant->setHPToMax();
}

void loopThroughCombat(std::vector<std::unique_ptr<Combatant>>& combatant)
{
    bool isAlive;
    std::cout << "COMBATANTS LISTED: \n";
    while ((alivePlayers > 0) && (aliveEnemies > 0))
    {
        for (std::unique_ptr<Combatant>& ele : combatant)
        {        
            isAlive = ele->isAlive();
            if(!isAlive)
            {
                
                if("Player" == ele->getType())
                {
                    alivePlayers = std::max(0, alivePlayers - 1);
                }
                else if("Enemy" == ele->getType())
                {
                    aliveEnemies = std::max(0, aliveEnemies - 1);
                }
                else
                {
                    /*Just catching invalid case*/
                }
                combatant.erase(
                    std::remove_if(combatant.begin(), combatant.end(), [](const std::unique_ptr<Combatant>& ele)
                    {
                        return !ele->isAlive();
                    }),
                        combatant.end()
                );
            }
            else
            {
                ele->takeTurn();
            }
        }
    }
}