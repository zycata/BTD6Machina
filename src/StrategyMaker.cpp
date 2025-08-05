#include "StrategyMaker.h"
#include "mouseControl/mouseControl.h"
#include "jsonHandlers/GameReader.h"
#include "gameTypes.h" // Contains Difficulty, GameResult, Tower, Action, UpgradeOption, PlacementOption, towerUpgrades, towerCosts, towerMap, towersAllowed, INVALID

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h> // For Sleep
#include <algorithm>


// Using an anonymous namespace for global constants that are only used in this file
namespace {
    // Assuming towerUpgrades, towerCosts, towerMap, towersAllowed, and INVALID are defined globally
    // or in gameTypes.hpp. If they are global, they should be extern in the .h and defined in a .cpp
    // For this example, I'm assuming they are accessible via gameTypes.hpp.
    // If they were truly global and only used here, they could be placed in an anonymous namespace.
}


StrategyMaker::StrategyMaker(Difficulty type, std::string filePath, std::vector<int> towersAllowed) : gameInfo(filePath),
    emptyUpgrade{0, 0, 0, 0, "", false} // Initialize emptyUpgrade here
{
    towerIdCounter = 1; // Initialize towerIdCounter
    gameInfo.initialize();

    TowersPlaced = {};
    TowersPlaced.reserve(1000);
    StrategyActions = {};
    StrategyActions.reserve(1000);
    this->towersAllowed = towersAllowed;
    // No need to reserve 1k but Justin Case (get it funny name pls laugh)
    // realistically tho this is never used i think i lowkey just got paranoid after accessing unsafe memory that one time

    this->currentRound = currentRound;

    startRound = gameInfo.getStartRound(); // games actual start round yes true true --> Literally irrelevent unless i do a funny true true but yes
    // so this is actually a weird btd6 feature???? but if you try getting the "startround" variable for each mode in btd6 the startRound for chimps, impoppable, or deflation you get, 3, 3 and 1 respectively.
    // As we all are pro btd6 players, we know that both chimps and impoppable start on 6, and deflation starts on 31. So turns out how btd6 is coded there's only technically "3" difficulties.
    // As demonstrated in the selection screen, and chimps and impoppable are subdifficulties of hard. I believe because the startRound variable represents the starting round for the main 3 difficulties, which doesn't include chimps impoppable or delfation
    // yeah because of this i have to hard code (literally just slap more stuff) siince yk yk yk
    // might make a mode for deflation, since it should be ALOT easier since you only technically have one round to place stuff

    totalTowers = gameInfo.getTowersPlaced(); // should always be zero.

    this->cash = gameInfo.getCash();

    this->type = type;

    switch (type) {
        case EASY:
            cashMultiplier = 0.85;
            currentRound = 1;
            break;
        case MEDIUM:
            cashMultiplier = 1.0;
            currentRound = 1 ;
            break;
        case HARD:
            cashMultiplier = 1.08;
            currentRound = 3;
            break;
        case IMPOPPABLE:
            cashMultiplier = 1.2;
            startRound = 6;
            currentRound = 6;
            break;
        case CHIMPS:
            cashMultiplier = 1.08;
            startRound = 6;
            currentRound = 6;
            break;
        default: // Handle unknown or uninitialized cases
            cashMultiplier = 1.0;
            currentRound = 1;
            break;
    }

    //std::cout << "Starting at Current round: " << currentRound << " Difficulty: " << to_string(type) << std::endl;

    // mouseControl::initializeMouseControls();
    srand(time(0));
}

bool StrategyMaker::isHeroAlreadyPlaced() {
    for ( auto& twr : TowersPlaced) {
        if (twr.isHero() ) {
            return true;
        }
    }
    return false;

}

void StrategyMaker::logTowers() {
    std::ofstream TowerFile("logs/towersPlaced.txt");
    TowerFile << "Towers placed: " << TowersPlaced.size() << std::endl;
    std::cout << "Towers placed: " << TowersPlaced.size() << std::endl;

    for (auto& tower : TowersPlaced) {
        // std::cout << "Tower ID: " << tower.getTowerId() << ", Type: " << tower.getTowerTypeStr() << ", Position: (" << tower.getX() << ", " << tower.getY() << ")" << ", Cross Pathing: " << tower.getCrossPathing() << ", Round Placed: " << tower.getRoundPlaced() << std::endl;
        TowerFile << "Tower ID: " << tower.getTowerId() << ", Type: " << tower.getTowerTypeStr() << ", Position: (" << tower.getX() << ", " << tower.getY() << ")" << ", Cross Pathing: " << tower.getCrossPathing() << ", Round Placed: " << tower.getRoundPlaced() << std::endl;
    }
}

void StrategyMaker::logStrategy() {
    std::ofstream StrategyFile("logs/strategyActions.txt");
    StrategyFile << "Strategy Actions: " << StrategyActions.size() << std::endl;
    for (auto& action : StrategyActions) {
        // std::cout << "Action Type: " << actionTypeToStr(action.type) << ", Tower ID: " << action.tower.getTowerId() << ", Position: (" << action.x << ", " << action.y << ")" << ", Tower Type: " << action.tower.getTowerTypeStr() << ", Path: " << action.path << ", Round: " << action.round << std::endl;
        StrategyFile << "Action Type: " << actionTypeToStr(action.type) << ", Tower ID: " << action.tower->getTowerId() << ", Position: (" << action.x << ", " << action.y << ")" << ", Tower Type: " << action.tower->getTowerTypeStr() << ", Path: " << action.path << ", Round: " << action.round << std::endl;
    }
}

void StrategyMaker::logItems() {
    logStrategy();
    logTowers();
}

void StrategyMaker::setCash(int cash) {
    this->cash = cash;
}

int StrategyMaker::getCash() {
    return this->cash;
}

int StrategyMaker::getCurrentRound() {
    return currentRound;
}

void StrategyMaker::incrementRound() {
    currentRound++;
}

std::vector<Tower> StrategyMaker::getTowersPlaced() {
    return TowersPlaced;
}

std::vector<Action> StrategyMaker::getStrategyActions() {
    return StrategyActions;
}

bool StrategyMaker::isValidBTD6Upgrade(std::array<int,3> path) {
    int numUsedPaths = 0;
    int numHighPaths = 0;

    for (int i = 0; i < 3; ++i) {
        if (path[i] >= 6) return false;  // Can't go above tier 5
        if (path[i] > 0) ++numUsedPaths;
        if (path[i] >= 3) ++numHighPaths;
    }

    return numUsedPaths <= 2 && numHighPaths <= 1;
}

int StrategyMaker::roundToNearest5(int num, float multiplier) {
    float value = num * multiplier;
    return static_cast<int>(5 * round(value / 5.0f));
}

//refactor soon
std::vector<UpgradeOption> StrategyMaker::getLegalUpgrades() {
    //returns all legal upgrades for the towers placed, cost not taken into account
    std::vector<UpgradeOption> legalUpgrades = {};
    for (auto& tower : TowersPlaced) {
        for (int i = 0; i < 3; i++) {
            int cost = towerUpgrades[tower.getTowerType()][i][tower.path[i]];

            if (cost == INVALID) continue; // Skip invalid upgrades
            if (tower.path[i] >= 5) continue; // Skip if already at max tier
            cost = roundToNearest5(cost, cashMultiplier); // OMG I FORGOT TS SYBAU I WAS WONDERING WHY THE VALUES WERE WRONG

            tower.path[i] += 1;
            if (isValidBTD6Upgrade(tower.path)) {
                UpgradeOption option;
                option.towerId = tower.getTowerId();
                option.path = i;
                option.cost = cost;
                option.tier = tower.path[i];
                option.towerTypeStr = tower.getTowerTypeStr();
                option.isAllowed = true; // Mark as allowed
                legalUpgrades.push_back(option);

            }
            tower.path[i] -= 1; // Reset path (probably a better way to do this ill implement later)
        }
    }
    return legalUpgrades;
}

std::vector<UpgradeOption> StrategyMaker::getAvailableUpgrades() {
    std::vector<UpgradeOption> availableUpgrades;
    for (auto& tower : TowersPlaced) {
        for (int i = 0; i < 3; i++) {
            int cost = towerUpgrades[tower.getTowerType()][i][tower.path[i]];

            if (cost == INVALID) continue; // Skip invalid upgrades

            if (tower.path[i] >= 5) continue; // Skip if already at max tier
            cost = roundToNearest5(cost, cashMultiplier);

            tower.path[i] += 1;
            if (isValidBTD6Upgrade(tower.path) && cost <= cash ) {
                UpgradeOption option;
                option.towerId = tower.getTowerId();
                option.path = i;
                option.cost = cost;
                option.tier = tower.path[i];
                option.towerTypeStr = tower.getTowerTypeStr();
                option.isAllowed = true; // Mark as allowed
                availableUpgrades.push_back(option);

            }
            tower.path[i] -= 1; // Reset the path for the next iteration
        }
    }
    return availableUpgrades;
}


std::vector<PlacementOption> StrategyMaker::getTowerPlacementOptions() {
    std::vector<PlacementOption> newTowers = {};
    for (auto& towerType : towersAllowed) {
        int cost = roundToNearest5(towerCosts[towerType], cashMultiplier);
        if (cost > cash) continue; // Skip if not enough cash
        if (cost == INVALID) continue; // Invalid type of upgrade ig ig ig true true

        if (towerType == 0 && isHeroAlreadyPlaced()) continue; //skip hero if already placed


        PlacementOption option;
        option.towerType = towerType;
        option.cost = cost;
        option.towerTypeStr = towerMap[towerType];
        newTowers.push_back(option);
    }
    return newTowers;
}

const char* StrategyMaker::actionTypeToStr(Action::ActionType type) {
    switch (type) {
        case Action::PLACE: return "PLACE";
        case Action::UPGRADE: return "UPGRADE";
        default: return "UNKNOWN";
    }
}

bool StrategyMaker::checkIfSuccessfullyPlaced() {
    //checks if the new gameinfo::getTowersPlaced() is greater than the previous one by a factor of 1
    int curTowers = gameInfo.getTowersPlaced();
    bool success = (totalTowers + 1) == curTowers; // check if the number of towers placed has increased
    bool cashChanged = (cash > gameInfo.getCash());
    return success && cashChanged; // Ensure both conditions are met
}
bool StrategyMaker::placeTower(int towerCode, int x, int y) {

    totalTowers = gameInfo.getTowersPlaced();
    mouseControl::placeTower(towerCode, x, y);
    Sleep(300); 
    int curTowers = gameInfo.getTowersPlaced();

    bool success = (curTowers == (totalTowers + 1)) && (this->cash != gameInfo.getCash()); 

    

    
    // bool success = checkIfSuccessfullyPlaced(); // Check if the placement was successful

    if (!success) {
        this->cash = gameInfo.getCash(); 
        std::cerr << "Tower placement failed." << std::endl;
        return false; 
    }
    totalTowers = gameInfo.getTowersPlaced(); // update total towers placed

    Tower newTower( x, y, towerCode, 0, 0, 0, currentRound, towerIdCounter );
    TowersPlaced.push_back(newTower);
    Tower* ptrToStoredTower = &TowersPlaced.back();
    // FUck i did the thing where i accessed invalid ram :sob: shoulda did this in scratch instead

    StrategyActions.push_back({Action::PLACE, ptrToStoredTower, x, y, towerCode, INVALID, currentRound, towerIdCounter});
    towerIdCounter++;

    this->cash = gameInfo.getCash(); 

    return true;
}

// TODO --> MAKE IT SO IT A TOWER ID IS FOUND TO HAVE FAILED ENOUGH TIMES MAKE IT SO THAT IT DELETES IT OFF (FAILED TO PLACETHE TOWER WHEN THOUGHT IT DID)
// towers failing to place and the codfe thinking it placed is pretty rare but it's happened (enough times) where im making ts (or fixin gplace towers idk)
// then goes to towers and strategy actions and deletes the tower (REMOVES IT SMITES IT YEET YEET)
// will also need a new system to ID towers after that but das easy (j'espere)
bool StrategyMaker::upgradeTower(int towerId, int path) {
    //implement mouse control later
    for (auto& tower : TowersPlaced) {
        if (tower.getTowerId() == towerId) {
            tower.path[path]++;
            mouseControl::upgradeTower(tower.getX(), tower.getY(), path);


            int cost = roundToNearest5(towerUpgrades[tower.getTowerType()][path][tower.path[path]], cashMultiplier);
            Sleep(200); // wait for the upgrade to be applied
            if (cash > gameInfo.getCash()) {
                this->cash = gameInfo.getCash(); // update cash after upgrade
                StrategyActions.push_back({Action::UPGRADE, &tower, tower.getX(), tower.getY(), tower.getTowerType(), path, currentRound, towerId});
                return true;

            } else if (cost > cash) {

                std::cerr << "Not enough cash to upgrade tower ID " << towerId << " on path " << path << ". Required: " << cost << ", Available: " << cash << std::endl;
                tower.path[path]--;

                return false; // Not enough cash
            } else {
                tower.path[path]--;
                return false; // upgrade failed for some reason
            }


        }
    }
    std::cerr << "Tower with ID " << towerId << " not found." << std::endl;
    return false; // Tower not found
}


// n2 > n1
// returns random int [n1, n2] (includes n1 and n2)
int StrategyMaker::getRandomInt(int n1, int n2) {
    // srand(time(nullptr));  // seed (only once in main ideally)
    return n1 + rand() % (n2 - n1 + 1);
}

// places a random tower... tries 5 times to place it before trying a new tower or giving up lmao
bool StrategyMaker::placeRandomTower(PlacementOption &selectedTower) {
    int maxAttempts = 6;
    // 6 attempts to place a tower 3 was wayyyy to low
    for (int i = 0; i < maxAttempts; i++) {
        int x = getRandomInt(xMin, xMAx);
        int y = getRandomInt(yMin, yMax);
        if (placeTower(static_cast<int>(selectedTower.towerType), x, y)) {
            this->cash = gameInfo.getCash();
            std::cout << "Placed tower of type " << selectedTower.towerTypeStr << " at (" << x << ", " << y << ")" << std::endl;
            return true;
        } else {

            std::cout << "Failed to place tower of type " << selectedTower.towerTypeStr << " at (" << x << ", " << y << ")" << std::endl;
            //system("pause");
        }
    }
    this->totalTowers = gameInfo.getTowersPlaced(); // update total towers placed
    this->cash = gameInfo.getCash(); // update cash after placement
    return false;
}

// pretty much places at most x towers randomly, but only if the towers are affordable immediately.
void StrategyMaker::placementAlgorithmOne(int maxAttempts) {
    this->cash = gameInfo.getCash(); // update cash before placement
    //int maxattempts = 4;
    for (int i = 0; i < maxAttempts; i++) {

        std::vector<PlacementOption> newTowers = getTowerPlacementOptions();
        if(newTowers.size() == 0) {
            std::cout << "No towers available for placement." << std::endl;
            return;
        } else {
            std::cout << "Towers available for placement: " << newTowers.size() << std::endl;
        }
        int randomNum = rand() % newTowers.size();
        PlacementOption selectedTower = newTowers[randomNum];
        placeRandomTower(selectedTower);
        std::cout << "Cash after placement: " << cash << std::endl;
    }

    std::cout << "No more towers can be placed or not enough cash." << std::endl;
    // system("pause");
}

void StrategyMaker::upgradeAlgorithmOne() {

    int maxAttempts = 7;


    for (int j = 0; j < maxAttempts; j++) {
        this->cash = gameInfo.getCash(); // update cash before upgrade
        std::vector<UpgradeOption> availableUpgrades = getAvailableUpgrades();
        if (availableUpgrades.size() == 0) {
            std::cout << "No upgrades available." << std::endl;

            return; // No upgrades available
        }

        int randomNum = rand() % availableUpgrades.size(); // Randomly select an upgrade

        UpgradeOption selectedUpgrade = availableUpgrades[randomNum];
        int maxtriestoupgrade = 3; // OH MY FUCKING GOD JUNK MEMORY CAN KYS
        for (int i = 0; i < maxtriestoupgrade; i++) {
            if (upgradeTower(selectedUpgrade.towerId, selectedUpgrade.path)) {
                std::cout << "Upgraded tower ID " << selectedUpgrade.towerId << " on path " << selectedUpgrade.path << " to tier " << selectedUpgrade.tier << std::endl;
                break;
            } else {
                std::cout << "Failed to upgrade tower ID " << selectedUpgrade.towerId << " on path " << selectedUpgrade.path << std::endl;

            }
            this->cash = gameInfo.getCash();
        }
    }


    this->cash = gameInfo.getCash(); // update cash after upgrade
}


void StrategyMaker::singleRoundLoopAlgorithmOne() {
    // make it slightly more prone to placing towers than upgrading
    // Ik magic numbers are bad but ill unmagic them soon^tm
    int choice = getRandomInt(1, 6); // Randomly choose between placing a tower or upgrading a tower
    if (choice <= 3 || totalTowers < 5) { // if total towers is less than 5, always place a tower
        std::cout << "Placing towers..." << std::endl;
        placementAlgorithmOne();
    } else {
        std::cout << "Upgrading towers..." << std::endl;
        upgradeAlgorithmOne();

    }

}

// function that selects an up grade for a tower --> only runs for higherRounds
// returns an upgrade option however it doesn't check if player has enough cash allowing the ai to "save up" for a tier 5 or something
// assuming it chooses an upgrade that the ai can afford on the spot, it'll just purchase it and buy it then run again or choose something else to run yes???
// AMONGLA SWAG pls work on this and lock in
UpgradeOption StrategyMaker::getTargetUpgrade() {
    std::vector<UpgradeOption> legalUpgrades = getLegalUpgrades();
    if (legalUpgrades.empty()) {
        std::cout << "No legal upgrades available." << std::endl;
        return emptyUpgrade; // No legal upgrades found
    }
    int randomNum = rand() % legalUpgrades.size(); // Randomly select an upgrade
    UpgradeOption selectedUpgrade = legalUpgrades[randomNum];
    std::cout << "Selected upgrade, Tower ID: " << selectedUpgrade.towerId << ", Path: " << selectedUpgrade.path << ", Cost: " << selectedUpgrade.cost << std::endl;
    return selectedUpgrade; // Return the selected upgrade
}

// remember to add chedk if it returns a valid upgrade
// add something to reason with the price lmao yes true true amongla swag....
UpgradeOption StrategyMaker::upgradeAlgorithmTwo() {
    int maxTowersUpgradedARound = 7;
    for (int j = 0; j < maxTowersUpgradedARound; j++) {
        UpgradeOption targetUpgrade = getTargetUpgrade();
        this->cash = gameInfo.getCash(); // update cash before upgrade
        if (targetUpgrade.isAllowed && targetUpgrade.cost <= cash) {
            if (upgradeTower(targetUpgrade.towerId, targetUpgrade.path)) {
                std::cout << "Upgraded tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << " to tier " << targetUpgrade.tier << std::endl;
            } else {
                std::cout << "Failed to upgrade tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << ". Not enough cash." << std::endl;

            }
        } else if (targetUpgrade.isAllowed && targetUpgrade.cost > cash) {
            std::cout << "Selected Target Upgrade, Not enough to Upgrade this round: " << currentRound << " on path " << targetUpgrade.path << " Tier: " << targetUpgrade.tier << ". Required: " << targetUpgrade.cost << ", Available: " << cash << std::endl;

            return targetUpgrade;
        }
    }
    this->cash = gameInfo.getCash(); // update cash after upgrade

    return emptyUpgrade; // Return an empty UpgradeOption if no upgrade was made
}

bool StrategyMaker::didRoundEnd() {
    // Check if the current round has ended
    if (gameInfo.getCurRound() > currentRound) {
        return true;
    }
    return false;
}

void StrategyMaker::startNextRound() {
    if (currentRound == startRound) {
        mouseControl::ClickStartNextRound();
        // click it twice for fast forward round 1 lmao not round one i meant if it was the first round 
    }

    mouseControl::ClickStartNextRound();
}

void StrategyMaker::useAbilities() {
    // std::cout << "Checking for Abilities that can be used..." << std::endl;
    int MAX_ABILITIES_THAT_CAN_BE_USED = 10;
    int DELAY_BETWEEN_ABILITIES = 150;
    std::vector<int> abilitiesAtOurDisposal = gameInfo.getAbilities();

    // Determine the number of abilities to check, using the smaller of the two values.
    int abilitiesToCheck =  (MAX_ABILITIES_THAT_CAN_BE_USED < abilitiesAtOurDisposal.size()) ? MAX_ABILITIES_THAT_CAN_BE_USED : abilitiesAtOurDisposal.size();
    std::vector<int> prevAbilities = abilitiesAtOurDisposal;
    
    for (int i = 0; i < abilitiesToCheck; ++i) {
        
        if (abilitiesAtOurDisposal[i] <= 0) {
            mouseControl::useAbility((i + 1) % MAX_ABILITIES_THAT_CAN_BE_USED);
            std::cout << "Using Ability: " << (i + 1) << std::endl;
            Sleep(DELAY_BETWEEN_ABILITIES);
        }
    }
    Sleep(DELAY_BETWEEN_ABILITIES);
    this->cash = gameInfo.getCash(); // to anybody reading this im doing this just to update the json (im lazy to make a better way)
    abilitiesAtOurDisposal = gameInfo.getAbilities();
    int firstTowerX = TowersPlaced.front().getX();
    int firstTowerY = TowersPlaced.front().getY();
    for (int i = 0; i < abilitiesToCheck; ++i) {
        
        if (abilitiesAtOurDisposal[i] <= 0 && prevAbilities[i] == abilitiesAtOurDisposal[i]) {
            // std::cout << "Ability cooldown: " << abilitiesAtOurDisposal[i] << std::endl;
            // mouseControl::useAbility((i + 1) % MAX_ABILITIES_THAT_CAN_BE_USED);
            Sleep(DELAY_BETWEEN_ABILITIES);
            mouseControl::clickOnTower(firstTowerX, firstTowerY);
            std::cout << "Using Ability: " << (i + 1) << std::endl;
            Sleep(DELAY_BETWEEN_ABILITIES);
        }
    }

}


int StrategyMaker::getPlacementChance(int curRound) {
    const int MIN_ROUND = 30;
    const int MAX_ROUND = 100;
    const int MAX_PLACEMENT_CHANCE = 30; // percent
    const int MIN_PLACEMENT_CHANCE = 1;  // percent

    int placementRange = MAX_ROUND - MIN_ROUND;
    int chanceRange = MAX_PLACEMENT_CHANCE - MIN_PLACEMENT_CHANCE;

    double ratio = static_cast<double>(curRound - MIN_ROUND) / placementRange;
    int placementChance = MAX_PLACEMENT_CHANCE - static_cast<int>(ratio * chanceRange);

    // Clamp placementChance between MIN_PLACEMENT_CHANCE and MAX_PLACEMENT_CHANCE
    if (placementChance < MIN_PLACEMENT_CHANCE) placementChance = MIN_PLACEMENT_CHANCE;
    else if (placementChance > MAX_PLACEMENT_CHANCE) placementChance = MAX_PLACEMENT_CHANCE;

    return placementChance;
}

GameResult StrategyMaker::runGame() {
    Finalizer logOnExit{[this] { this->logItems(); }};

    bool gameOver = false;
    UpgradeOption targetUpgrade = emptyUpgrade;

    while (!gameOver) {

        if (this->currentRound < 30) {
            singleRoundLoopAlgorithmOne();
        } else {
            int roll = getRandomInt(1, 100);
            int placementChance = getPlacementChance(this->currentRound);

            // general flow chart:
            // isThere a target upgrade? yes -> upgrade it no? save up 
            // after yes, check roll for placing or upgrading for another target upgrade.
            if (targetUpgrade.isValid() && targetUpgrade.cost <= cash) {
                std::cout << "UPGRADING TOWER THAT HAS BEEN SAVED UP FOR" << std::endl;
                std::cout << "Upgraded tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << " to tier " << targetUpgrade.tier << std::endl;
                targetUpgrade = emptyUpgrade;
            }

            if (targetUpgrade.isValid() && targetUpgrade.cost > cash) {
                std::cout << "Still saving up to upgrade tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << ". Required: " << targetUpgrade.cost << ", Available: " << cash << std::endl;
                std::cout << "saving for the target upgrade...." << std::endl;
                    // do nothing, save up for the target upgrade
            }
            else if (roll <= placementChance) { 
                // Placement algorithm two guys trust me imma lock tf in
                std::cout << "Placing towers" << std::endl;
                placementAlgorithmOne(); // guys im siorry but plcaement algorithm one is cracked...
            }
            else {
                targetUpgrade = upgradeAlgorithmTwo(); 
            }
        }


        startNextRound();
        std::cout << "Waiting for next round..." << std::endl;

        bool roundOver = false;
        while (!roundOver) {
            // std::cout << "Game over? " << (gameOver ? "Yes" : "No") << std::endl;
            int newRound = gameInfo.getCurRound();
            if (this->currentRound != newRound) {
                std::cout << "Round changed from " << this->currentRound << " to " << newRound << std::endl;
                this->currentRound = newRound;

                roundOver = true;

                if (gameInfo.didGameWon()) {
                    std::cout << "Game Won!" << std::endl;
                    return GameResult::VICTORY;
                    //return; // exit the game loop
                }
            }
            else if (gameInfo.didGameOver()) {
                std::cout << "Game Over!" << std::endl;
                return GameResult::DEFEAT;
            } else {
                useAbilities();
            }
            Sleep(500);

        }


        this->currentRound = gameInfo.getCurRound();
        this->cash = gameInfo.getCash();
        std::cout << "Current round: " << this->currentRound << std::endl;


        std::cout << "Game is still ongoing." << std::endl;
    }
    return GameResult::DEFEAT; // Should not be reached if game ends
}

/* Okay let me think of a design process here
basically it receives a vector of actions, and executes them in order pretty much,
so lets start, since this must always be called right as the game starts, we can start by checking if
the round is active.
-> isroundactive? -> if true -> wait
-> if false -> increment the vectors -> is action current round? -> yes? -> continue
-> if no then wait for next round, check again

hey that wasn't too bad, also used a pointer because i think im so cool
so glad no need to allocate heap i could never :sob:
*/

// TODO: this has overlap with the previous function, so maybe make a helper or combine these two?
// should be possible for sure, anyways im done for the day tommorow for file gen with jsonManager finally
GameResult StrategyMaker::followStrategy(const std::vector<Action>& parentStrategy) {
    Finalizer logOnExit{[this] { this->logItems(); }};

    if (parentStrategy.empty()) {
        return GameResult::FINISHEDSTRATEGY;
    }

    bool gameOver = false;
    std::size_t maxPointerSize = parentStrategy.size(); // Use std::size_t for size
    int pointer = 0;
    // start pointer at the first object
    const Action *curAction = nullptr; // Initialize to nullptr
    if (maxPointerSize > 0) {
        curAction = &parentStrategy[pointer];
    } else {
        // If there's no strategy, just return FINISHEDSTRATEGY
        // i just realiezd my empty guard does that already but it does not hurt to be safe amirite guys
        return GameResult::FINISHEDSTRATEGY;
    }

    int nextRoundToAct = curAction->round;
    while (!gameOver) {
        bool roundOver = false;

        while (nextRoundToAct == currentRound) {
            if(curAction->type == Action::PLACE) {
                std::cout << "Placing towers from strategy" << std::endl;
                placeTower(curAction->towerType, curAction->x, curAction->y);

            } else if (curAction->type == Action::UPGRADE) {
                std::cout << "Upgrading towers from strategy" << std::endl;

                upgradeTower(curAction->towerId, curAction->path);
            }
            pointer++; // increment the pointer on the vector
            if (pointer >= maxPointerSize) {
                return GameResult::FINISHEDSTRATEGY;
            }
            curAction = &parentStrategy[pointer];
            nextRoundToAct = curAction->round;
        }
        startNextRound();
        std::cout << "waiting for round to be over..." << std::endl;
        while (!roundOver) {
            // std::cout << "Game over? " << (gameOver ? "Yes" : "No") << std::endl;
            int newRound = gameInfo.getCurRound();
            if (this->currentRound != newRound) {
                std::cout << "Round changed from " << this->currentRound << " to " << newRound << std::endl;
                this->currentRound = newRound;

                roundOver = true;

                if (gameInfo.didGameWon()) {
                    std::cout << "Game Won!" << std::endl;

                    return GameResult::VICTORY;
                    //return; // exit the game loop
                }
            }
            else if (gameInfo.didGameOver()) {
                std::cout << "Game Over!" << std::endl;

                return GameResult::DEFEAT;
            } else {
                useAbilities();
            }

            Sleep(500);

        }
        
        this->currentRound = gameInfo.getCurRound();
        this->cash = gameInfo.getCash();
        std::cout << "Current round: " << this->currentRound << std::endl;


        std::cout << "Game is still ongoing." << std::endl;

    }
    return GameResult::DEFEAT; // Should not be reached if game ends
}


GameResult StrategyMaker::generateStrategy(std::vector<Action>& parentStrategy) {
    GameResult followedResult = followStrategy(parentStrategy);
    switch(followedResult) {
        case(FINISHEDSTRATEGY):
            break;
        case(VICTORY):
            return followedResult;
            break;
        case(DEFEAT):
            return followedResult;
            break;
        default:
            std::cerr << "fuking fail" << std::endl;
            break;

    }
    return runGame();

}

// check if the gamemode is chimps if it is the starting round, the restart button is in a diff position
// idk honestly kinda wack but not a huge difference
void StrategyMaker::restartGame() {
    if (this->currentRound == startRound && this->type == Difficulty::CHIMPS) {
        mouseControl::restartGameWhenOver(true);
    } else {
        mouseControl::restartGameWhenOver(false);
    }
}