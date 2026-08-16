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

void runCombat(Combatant** playerturn, int count);
void buildParty();
void printRoster(const std::vector<Combatant*>& combatant);
void addCombatant(std::vector<std::unique_ptr<Combatant>>& combatant);
void resetHP(Combatant*& combatant);
void doDamage();

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
    std::cin.ignore();
    alivePlayers = num_of_characters;

    try
    {
        if (num_of_characters < 1)
        {        
            throw std::invalid_argument("Invalid number of player characters");
        }
        for(int i = 0; i < num_of_characters; i++)
        {
            std::cout << "Enter the name, and class of the player character in the following format: <name>'<class> ";
            std::string line;
            std::getline(std::cin, line);

            size_t apostrophe = line.find('\'');
            character_name = line.substr(0, apostrophe);
            playerinfo_class = line.substr(apostrophe + 1);

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
    std::cin.ignore();
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
            std::getline(std::cin, character_name);
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
    
    loopThroughCombat(Combatants);

    return 0;
}


void addCombatant(std::vector<std::unique_ptr<Combatant>>& combatant)
{
    combatant.push_back(std::make_unique<PlayerCharacter>("Jim",15,16,12,0,"Warlock",2));
    std::cout<< "JIM IS HERE" << std::endl;
}


void resetHP(Combatant*& combatant)
{
    combatant->setHPToMax();
}

void loopThroughCombat(std::vector<std::unique_ptr<Combatant>>& combatant)
{
    int input;
    ActionType action_selected = ActionType::NONE;
    std::cout << "COMBATANTS LISTED: \n";
    while ((alivePlayers > 0) && (aliveEnemies > 0))
    {
        for (size_t i = 0; i < combatant.size(); /* no increment here */)
        {
            if (!combatant[i]->isAlive())
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
            }
            else
            {
                std::cout << "Choose your action, by typing its' number: \n1: Attack \n2: Skip \n3: End encounter \n";
                std::cin >> input;
                std::cin.ignore();
                action_selected = static_cast<ActionType>(input);
                if(action_selected == ActionType::ATTACK)
                {
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
                    std::cin >> target;
                    std::cin.ignore();
                    auto it = std::find_if(combatant.begin(), combatant.end(),
                    [&target](const std::unique_ptr<Combatant>& ele)
                    {
                        return ele->getName() == target;
                    });
                    if (it != combatant.end())
                    {
                        combatant[i]->takeTurn(action_selected, it->get());
                    }
                    else
                    {
                        std::cout << "Invalid target name. Turn skipped.\n";
                    }
                }
                else
                {
                    combatant[i]->takeTurn(action_selected);
                }
                i++; 
            }
        }
    }
}

void doDamage()
{

}
