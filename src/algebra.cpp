#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>


#include "mouseControl/mouseControl.h"
#include "jsonHandlers/GameReader.h"
#include "gameTypes.hpp"
using namespace std;
/*
namespace mouseControl {dddint y) {return true;};
    void upgradeTower(int x, int y, int path) {};
    bool findWindow() {return true;};
    bool initializeMouseControls() {return true;};
    void ClickStartNextRound() {};
}

namespace gameInfo {f
    int getCash();
    int getStartRound();
    int getCurRound();
    int getLives();
    int getTowersPlaced();
    int getTotalAbilities();
    int getLogNumber();
    bool roundChanged();
    bool isGameOver();
    bool isGameWon();
}
*/
// compile using g++ src/algebra.cpp src/jsonHandlers/GameReader.cpp src/mouseControl/mouseControl.cpp -o ATestSetting/aitd6


void printAvailableUpgrades(const vector<UpgradeOption>& upgrades) {
    cout << "Available Upgrades:" << endl;
    for (const auto& upgrade : upgrades) {
        cout << "Tower Type: " << upgrade.towerTypeStr << ", Tower ID: " << upgrade.towerId << ", Path: " << upgrade.path << ", Upgrade Tier: " << upgrade.tier << ", Cost: " << upgrade.cost << endl;
    }
}

void printTowerPlacementOptions(const vector<PlacementOption>& options) {
    cout << "Available Tower Placement Options:" << endl;
    for (const auto& option : options) {
        cout << "Tower Type: " << option.towerTypeStr << ", Tower ID: " << option.towerType << ", Placement Cost: " << option.cost << endl;
    }
}

class StrategyMaker {
    private:
        vector<Tower> TowersPlaced;
        vector<Action> StrategyActions;
        int currentRound;
        int totalTowers;
        int cash;
        Difficulty type;
        
        float cashMultiplier;

        GameReader gameInfo;

        const int xMAx = 1000;
        const int yMax = 720;
        const int yMin = 40;
        const int xMin = 25;

        int startRound;
        const UpgradeOption emptyUpgrade = {0, 0, 0, 0, "", false}; // Empty upgrade option to return when no upgrades are available
    public:
        StrategyMaker(Difficulty type, string filePath) : gameInfo(filePath)
        {
            gameInfo.initialize();

            TowersPlaced = {};
            TowersPlaced.reserve(1000);
            //No need to reserve 1k but Justin Case (get it funny name pls laugh)
            // will probably reserve 1k for strategy actions idk why not lmao
            StrategyActions = {};
            this->currentRound = currentRound;
            
            startRound = gameInfo.getStartRound(); // games actual start round yes true true --> Literally irrelevent unless i do a funny true true but yes 
            
            totalTowers = gameInfo.getTowersPlaced();
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
                    currentRound = 6;
                    break;
                case CHIMPS:
                    cashMultiplier = 1.2;
                    currentRound = 6;
                    break;
            
            cout << "Starting at Current round: " << currentRound << "Difficulty: " << type << endl;

            }
            
            // mouseControl::initializeMouseControls();
            srand(time(0));
        }

        void setCash(int cash) {
            this->cash = cash;
        }

        int getCurrentRound() {
            return currentRound;
        }

        void incrementRound() {
            currentRound++;
        }

        vector<Tower> getTowersPlaced() {
            return TowersPlaced;
        }

        vector<Action> getStrategyActions() {
            return StrategyActions;
        }

        bool isValidBTD6Upgrade(array<int,3> path) {
            int numUsedPaths = 0;
            int numHighPaths = 0;

            for (int i = 0; i < 3; ++i) {
                if (path[i] >= 6) return false;  // Can't go above tier 5
                if (path[i] > 0) ++numUsedPaths;
                if (path[i] >= 3) ++numHighPaths;
            }

            return numUsedPaths <= 2 && numHighPaths <= 1;
        }

        int roundToNearest5(int num, float multiplier) {
            float value = num * multiplier;
            return static_cast<int>(5 * round(value / 5.0f));
        }

        //refactor soon
        vector<UpgradeOption> getLegalUpgrades() { 
            //returns all legal upgrades for the towers placed, cost not taken into account
            vector<UpgradeOption> legalUpgrades = {};
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
                        legalUpgrades.push_back(option);

                    } 
                    tower.path[i] -= 1; // Reset path (probably a better way to do this ill implement later)
                }
            }
            return legalUpgrades;
        }
        vector<UpgradeOption> getAvailableUpgrades() {
            vector<UpgradeOption> availableUpgrades;
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
                        availableUpgrades.push_back(option);

                    } 
                    tower.path[i] -= 1; // Reset the path for the next iteration
                }
            }
            return availableUpgrades;
        }

        bool isHeroAlreadyPlaced() {
            for ( auto& twr : TowersPlaced) {
                if (twr.isHero() ) {
                    return true; 
                }
            }
            return false;

        }

        vector<PlacementOption> getTowerPlacementOptions() {
            vector<PlacementOption> newTowers = {};
            for (auto& towerType : towersAllowed) {
                int cost = roundToNearest5(towerCosts[towerType], cashMultiplier);
                if (cost > cash) continue; // Skip if not enough cash


                if (towerType == 0 && isHeroAlreadyPlaced()) continue; //skip hero if already placed

                

                PlacementOption option;
                option.towerType = towerType;
                option.cost = cost;
                option.towerTypeStr = towerMap[towerType];
                newTowers.push_back(option);
            }
            return newTowers;
        }

        const char* actionTypeToStr(Action::ActionType type) {
            switch (type) {
                case Action::PLACE: return "PLACE";
                case Action::UPGRADE: return "UPGRADE";
                default: return "UNKNOWN";
            }
        }

        bool checkIfSuccessfullyPlaced() {
            //checks if the new gameinfo::getTowersPlaced() is greater than the previous one by a factor of 1
            int curTowers = gameInfo.getTowersPlaced();
            totalTowers++;
            return (totalTowers) == curTowers; // check if the number of towers placed has increased
        }

        bool placeTower(int towerCode, int x, int y) {
            //implement mouse control later
            mouseControl::placeTower(towerCode, x, y);
            Sleep(200); // wait for the tower to be placed
            // check if placement was successful
            totalTowers++;
            int curTowers = gameInfo.getTowersPlaced();
            cout << "Total Towers: " << totalTowers << ", Current Towers: " << curTowers << endl;
            bool success = (totalTowers) == curTowers; // check if the number of towers placed has increased
            
            // bool success = getInput(); // manually tell ai if the placement was successful
            if (!success) {
                totalTowers--; // revert the total towers count if placement failed

                cerr << "Tower placement failed." << endl;
                return false; // Placement failed
            }
            
            Tower newTower( x, y, towerCode, 0, 0, 0, currentRound, totalTowers );
            TowersPlaced.push_back(newTower);
            Tower* ptrToStoredTower = &TowersPlaced.back();
            // FUck i did the thing where i accessed invalid ram :sob: shoulda did this in scratch instead

            StrategyActions.push_back({Action::PLACE, ptrToStoredTower, x, y, towerCode, INVALID, currentRound, totalTowers});
            //cout << "Placed tower of type " << newTower.towerType << " at (" << x << ", " << y << ")" << endl;
            this->cash = gameInfo.getCash(); // update cash after placement

            return true;
        }

        // TODO --> MAKE IT SO IT A TOWER ID IS FOUND TO HAVE FAILED ENOUGH TIMES MAKE IT SO THAT IT DELETES IT OFF (FAILED TO PLACETHE TOWER WHEN THOUGHT IT DID)
        // towers failing to place and the codfe thinking it placed is pretty rare but it's happened (enough times) where im making ts (or fixin gplace towers idk)
        // then goes to towers and strategy actions and deletes the tower (REMOVES IT SMITES IT YEET YEET)
        // will also need a new system to ID towers after that but das easy (j'espere)
        bool upgradeTower(int towerId, int path) {
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
                        
                        cerr << "Not enough cash to upgrade tower ID " << towerId << " on path " << path << ". Required: " << cost << ", Available: " << cash << endl;
                        tower.path[path]--;

                        return false; // Not enough cash
                    } else {
                        tower.path[path]--;
                        return false; // upgrade failed for some reason
                    }


                    
                }
            }
            cerr << "Tower with ID " << towerId << " not found." << endl;
            return false; // Tower not found
        }

        void logTowers() {
            ofstream TowerFile("logs/towersPlaced.txt");
            TowerFile << "Towers placed: " << TowersPlaced.size() << endl;
            cout << "Towers placed: " << TowersPlaced.size() << endl;

            for (auto& tower : TowersPlaced) {
                // cout << "Tower ID: " << tower.getTowerId() << ", Type: " << tower.getTowerTypeStr() << ", Position: (" << tower.getX() << ", " << tower.getY() << ")" << ", Cross Pathing: " << tower.getCrossPathing() << ", Round Placed: " << tower.getRoundPlaced() << endl;
                TowerFile << "Tower ID: " << tower.getTowerId() << ", Type: " << tower.getTowerTypeStr() << ", Position: (" << tower.getX() << ", " << tower.getY() << ")" << ", Cross Pathing: " << tower.getCrossPathing() << ", Round Placed: " << tower.getRoundPlaced()  << endl;
            }
        }

        void logStrategy() {
            ofstream StrategyFile("logs/strategyActions.txt");
            StrategyFile << "Strategy Actions: " << StrategyActions.size() << endl;
            for (auto& action : StrategyActions) {
                // cout << "Action Type: " << actionTypeToStr(action.type) << ", Tower ID: " << action.tower.getTowerId() << ", Position: (" << action.x << ", " << action.y << ")" << ", Tower Type: " << action.tower.getTowerTypeStr() << ", Path: " << action.path << ", Round: " << action.round  << endl;
                StrategyFile << "Action Type: " << actionTypeToStr(action.type) << ", Tower ID: " << action.tower->getTowerId() << ", Position: (" << action.x << ", " << action.y << ")" << ", Tower Type: " << action.tower->getTowerTypeStr()  << ", Path: " << action.path  << ", Round: " << action.round  << endl;
            }
        }

        // n2 > n1
        // returns random int [n1, n2] (includes n1 and n2)
        int getRandomInt    (int n1, int n2) {
            // srand(time(nullptr));  // seed (only once in main ideally)
            return n1 + rand() % (n2 - n1 + 1);
        }

        // places a random tower... tries 5 times to place it before trying a new tower or giving up lmao 
        bool placeRandomTower(PlacementOption &selectedTower) {
            int maxAttempts = 3;
            // 5 attempts to place a tower
            for (int i = 0; i < maxAttempts; i++) {
                    int x = getRandomInt(xMin, xMAx);
                    int y = getRandomInt(yMin, yMax);
                    if (placeTower(selectedTower.towerType, x, y)) {
                        this->cash = gameInfo.getCash();
                        cout << "Placed tower of type " << selectedTower.towerTypeStr << " at (" << x << ", " << y << ")" << endl;
                        return true;
                    } else {
                        
                        cout << "Failed to place tower of type " << selectedTower.towerTypeStr << " at (" << x << ", " << y << ")" << endl;
                        //system("pause");
                    }
                }
            this->totalTowers = gameInfo.getTowersPlaced(); // update total towers placed
            this->cash = gameInfo.getCash(); // update cash after placement
            return false; 
        }

        // pretty much places at most 5 towers randomly, but only if the towers are affordable immediately. 
        void placementAlgorithmOne() {
            
            int maxattempts = 5;
            for (int i = 0; i < maxattempts; i++) {
            
                vector<PlacementOption> newTowers = getTowerPlacementOptions();
                if(newTowers.size() == 0) {
                    cout << "No towers available for placement." << endl;
                    return;
                } else {
                    cout << "Towers available for placement: " << newTowers.size() << endl;
                }
                int randomNum = rand() % newTowers.size(); 
                PlacementOption selectedTower = newTowers[randomNum];
                placeRandomTower(selectedTower);
                cout << "Cash after placement: " << cash << endl;
            } 
            
            cout << "No more towers can be placed or not enough cash." << endl;
            // system("pause");
        }
        
        void upgradeAlgorithmOne() {

            int maxAttempts = 7;
            
            
            for (int j = 0; j < maxAttempts; j++) { 
                vector<UpgradeOption> availableUpgrades = getAvailableUpgrades();
                if (availableUpgrades.size() == 0) {
                    cout << "No upgrades available." << endl;
                    
                    return; // No upgrades available
                }

                int randomNum = rand() % availableUpgrades.size(); // Randomly select an upgrade

                UpgradeOption selectedUpgrade = availableUpgrades[randomNum];
                for (int i = 0; i < maxAttempts; i++) {
                if (upgradeTower(selectedUpgrade.towerId, selectedUpgrade.path)) {
                    cout << "Upgraded tower ID " << selectedUpgrade.towerId << " on path " << selectedUpgrade.path << " to tier " << selectedUpgrade.tier << endl;
                    break;
                } else {
                    cout << "Failed to upgrade tower ID " << selectedUpgrade.towerId << " on path " << selectedUpgrade.path << endl;
                    
                }
                this->cash = gameInfo.getCash();
            }
            }
            
            
            this->cash = gameInfo.getCash(); // update cash after upgrade
        }

        
        void singleRoundLoopAlgorithmOne() {
            // make it slightly more prone to placing towers than upgrading 
            int choice = getRandomInt(1, 5); // Randomly choose between placing a tower or upgrading a tower
            if (choice <= 3 || totalTowers < 5) { // if total towers is less than 5, always place a tower
                cout << "Placing towers..." << endl;
                placementAlgorithmOne();
            } else {
                cout << "Upgrading towers..." << endl;
                upgradeAlgorithmOne();
                
            }

        }

        // function that selects an up grade for a tower --> only runs for higherRounds
        // returns an upgrade option however it doesn't check if player has enough cash allowing the ai to "save up" for a tier 5 or something
        // assuming it chooses an upgrade that the ai can afford on the spot, it'll just purchase it and buy it then run again or choose something else to run yes???
        // AMONGLA SWAG pls work on this and lock in 
        UpgradeOption getTargetUpgrade() {
            vector<UpgradeOption> legalUpgrades = getLegalUpgrades();
            if (legalUpgrades.empty()) {
                cout << "No legal upgrades available." << endl;
                return emptyUpgrade; // No legal upgrades found
            }
            int randomNum = rand() % legalUpgrades.size(); // Randomly select an upgrade
            UpgradeOption selectedUpgrade = legalUpgrades[randomNum];
            cout << "Selected upgrade, Tower ID: " << selectedUpgrade.towerId << ", Path: " << selectedUpgrade.path << ", Cost: " << selectedUpgrade.cost << endl;
            return selectedUpgrade; // Return the selected upgrade
        }

        // remember to add chedk if it returns a valid upgrade
        // add something to reason with the price lmao yes true true amongla swag....
        UpgradeOption upgradeAlgorithmTwo() {
            int maxAttempts = 7;
            for (int j = 0; j < maxAttempts; j++) {
                UpgradeOption targetUpgrade = getTargetUpgrade();
                if (targetUpgrade.cost <= cash) {
                    if (upgradeTower(targetUpgrade.towerId, targetUpgrade.path)) {
                        cout << "Upgraded tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << " to tier " << targetUpgrade.tier << endl;
                    } else {
                        cout << "Failed to upgrade tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << ". Not enough cash." << endl;
                        
                    }
                } else if (targetUpgrade.cost > cash) {
                    cout << "Selected Target Upgrade, Not enough to Upgrade this round: " << currentRound << " on path " << targetUpgrade.path << " Tier: " << targetUpgrade.tier << ". Required: " << targetUpgrade.cost << ", Available: " << cash << endl;\
                    
                    return targetUpgrade;
                }
            }
            this->cash = gameInfo.getCash(); // update cash after upgrade

            return emptyUpgrade; // Return an empty UpgradeOption if no upgrade was made
        }

        
        // !!! TODO: make shitty ai restart the game using the restart button thing when the game is over
        
        GameResult runGame() {
            bool gameOver = false;
            UpgradeOption targetUpgrade = emptyUpgrade;

            while (!gameOver) {
                
                if (this->currentRound < 30) {
                    singleRoundLoopAlgorithmOne();
                } else {
                    int choice = getRandomInt(1, 4); // Randomly choose between placing a tower or upgrading a tower --> higher chacne of upgrading a tower
                    if (choice == 1) { // if total towers is less than 5, always place a tower
                        // Placement algorithm two guys trust me imma lock tf in
                        cout << "Placing towers" << endl;
                        placementAlgorithmOne(); // guys im siorry but plcaement algorithm one is cracked...
                    }
                    else {
                        // pretty much selec ts a target upgrade yes yes true true....
                        // if (targetUpgrade) pretty much just checks if it is null
                        if (targetUpgrade.isAllowed && targetUpgrade.cost <= cash) {
                            upgradeTower(targetUpgrade.towerId, targetUpgrade.path);
                            cout << "UPGRADING TOWER THAT HAS BEEN SAVED UP FOR" << endl;
                            cout << "Upgraded tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << " to tier " << targetUpgrade.tier << endl;
                            targetUpgrade = emptyUpgrade; 
                        } else if (targetUpgrade.isAllowed && targetUpgrade.cost > cash) {
                            cout << "Not enough cash to upgrade tower ID " << targetUpgrade.towerId << " on path " << targetUpgrade.path << ". Required: " << targetUpgrade.cost << ", Available: " << cash << endl;
                            cout << "saving for the target upgrade...." << endl;
                            // do nothing, save up for the target upgrade
                        }
                        else {
                            targetUpgrade = upgradeAlgorithmTwo(); // get a new target upgrade
                        }
                    }
                }
                
                if (currentRound == startRound) {
                    mouseControl::ClickStartNextRound();
                    // click it twice for fast forward round 1 lmao
                }
                
                mouseControl::ClickStartNextRound();
                
                cout << "Waiting for next round..." << endl;
                
                bool roundOver = false;
                while (!roundOver) {
                    gameOver = gameInfo.didGameOver();
                    cout << "Game over? " << (gameOver ? "Yes" : "No") << endl;
                    if (this->currentRound != gameInfo.getCurRound()) {
                        cout << "Round changed from " << this->currentRound << " to " << gameInfo.getCurRound() << endl;
                        this->currentRound = gameInfo.getCurRound();

                        roundOver = true;

                        if (gameInfo.didGameWon()) {
                            cout << "Game Won!" << endl;
                            logStrategy();
                            logTowers();
                            return GameResult::VICTORY;
                            //return; // exit the game loop
                        }
                    } 
                    else if (gameInfo.didGameOver()) {
                        gameOver = true;
                        break; 
                    }
                    Sleep(200); 

                }
                // gameOver = getInput(); // manually tell ai if the game is over
                if (gameOver == true) {
                    cout << "Game Over!" << endl;
                    logStrategy();
                    logTowers();
                    return GameResult::DEFEAT; 
                    //break;
                }
                this->currentRound = gameInfo.getCurRound();
                this->cash = gameInfo.getCash();
                cout << "Current round: " << this->currentRound << endl;
                
                
                cout << "Game is still ongoing." << endl;
            }
        }
};





int main() {
    
    string filePath = "D:/Gamesfiles/Steam/steamapps/common/BloonsTD6/gameData/gameData.json";

    cout << "Script Started" << endl;
    
    
    cout << "Starting game..." << endl;
    bool found = mouseControl::findWindow(); // find the game window
    if (!mouseControl::findWindow()) {
        cerr << "Game window not found. Please ensure the game is running." << endl;
        return 1; // Exit if the game window is not found
    }
    system("pause");
    
    /*
    strategy.placeTower(1, 100, 200);
    strategy.upgradeTower(0, 1);
    strategy.upgradeTower(0, 1);
    strategy.upgradeTower(0, 1);
    strategy.upgradeTower(0, 1);
    strategy.upgradeTower(0, 1);
    strategy.upgradeTower(0, 2);
    strategy.upgradeTower(0, 2);

    strategy.incrementRound();
    strategy.placeTower(9, 300, 400);
    strategy.placeTower(13, 500, 600);
    strategy.logTowers();
    printAvailableUpgrades(strategy.getAvailableUpgrades());
    printTowerPlacementOptions(strategy.getTowerPlacementOptions());*/
    
    while (true) {
        StrategyMaker strategy(Difficulty::HARD, filePath);
        if (strategy.runGame() == GameResult::VICTORY) {
            break;
        } else {
            cout << "tryna new strat " << endl;
            Sleep(1000);
            mouseControl::restartGameWhenOver(false);
        }
        Sleep(1000);
    }
    
    cout << "game has been finished" << endl;
    system("pause");
    return 0;
}
