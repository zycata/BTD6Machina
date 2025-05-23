#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cmath>
// #include "mouseControl/mouseControl.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
namespace mouseControl {
    bool placeTower(int tower, int x, int y) {return true;};
    void upgradeTower(int x, int y, int path) {};
    bool findWindow() {return true;};
    bool initializeMouseControls() {return true;};
    void ClickStartNextRound() {};
}
// compile using g++ src/algebra.cpp src/mouseControl/mouseControl.cpp -o src/aitd6

map<int, string> towerMap = {
    {0, "Hero"},
    {1, "Dart Monkey"},
    {2, "Boomerang Monkey"},
    {3, "Bomb Shooter"},
    {4, "Tack Shooter"},
    {5, "Ice Monkey"},
    {6, "Glue Gunner"},
    {7, "Sniper Monkey"},
    {8, "Monkey Sub"},
    {9, "Monkey Buccaneer"},
    {10, "Monkey Ace"},
    {11, "Heli Pilot"},
    {12, "Mortar Monkey"},
    {13, "Dartling Gunner"},
    {14, "Wizard Monkey"},
    {15, "Super Monkey"},
    {16, "Ninja Monkey"},
    {17, "Alchemist"},
    {18, "Druid"},
    {19, "Mermonkey"},
    {20, "Banana Farm"},
    {21, "Spike Factory"},
    {22, "Monkey Village"},
    {23, "Engineer Monkey"},
    {24, "Beast Handler"}
};

const int INVALID = -1;
const int towerUpgrades[25][3][5] = {
    
    {
        // Hero (upgrading hero is not allowed)
        {INVALID, INVALID, INVALID, INVALID, INVALID}, 
        {INVALID, INVALID, INVALID, INVALID, INVALID}, 
        {INVALID, INVALID, INVALID, INVALID, INVALID  }  
    },

    // Dart Monkey
    {
        {140, 200, 320, 1800, 15000}, // Path 1
        {100, 190, 450, 7200, 45000}, // Path 2
        {90, 200, 575, 2050, 21500}   // Path 3
    },
    // Boomerang Monkey
    {
        {200, 280, 600, 2000, 32500},
        {175, 250, 1250, 4200, 35000},
        {100, 300, 1300, 2400, 50000}
    },
    // Bomb Shooter
    {
        {250, 650, 1100, 2800, 55000},
        {250, 400, 1000, 3450, 28000},
        {200, 300, 700, 2500, 23000}
    },
    // Tack Shooter
    {
        {150, 300, 600, 3500, 45500},
        {100, 225, 550, 2700, 15000},
        {110, 110, 450, 3200, 20000}
    },
    // Ice Monkey
    {
        {150, 350, 1500, 2200, 28000},
        {225, 450, 2500, 4000, 19200},
        {175, 225, 1750, 2750, 30000}
    },
    // Glue Gunner
    {
        {200, 300, 2000, 5000, 22500},
        {100, 970, 1950, 4000, 16000},
        {280, 400, 3600, 4000, 24000}
    },
    // Sniper Monkey
    {
        {350, 1300, 2500, 6000, 32000},
        {250, 450, 2100, 7600, 14000},
        {450, 450, 2900, 4100, 14700}
    },
    // Monkey Sub
    {
        {130, 500, 700, 2300, 28000},
        {450, 300, 1350, 13000, 29000},
        {450, 1000, 1100, 2500, 25000}
    },
    // Monkey Buccaneer
    {
        {275, 425, 3050, 8000, 24500},
        {550, 500, 900, 3900, 27000},
        {200, 350, 2400, 5500, INVALID} //23000} // tell ai to not upgrade a boat to trade empire
    },
    // Monkey Ace
    {
        {650, 650, 1000, 3000, 42500},
        {200, 350, 900, 18000, 30000},
        {500, 550, 2550, 23400, 85000}
    },
    // Heli Pilot
    {
        {800, 500, 1850, 19600, 45000},
        {300, 600, 3500, 9500, 30000},
        {250, 350, 3100, 8500, 35000}
    },
    // Mortar Monkey
    {
        {500, 500, 825, 7200, 36000},
        {300, 500, 900, 6500, 38000},
        {200, 500, 900, 9500, 40000}
    },
    // Dartling Gunner
    {
        {300, 900, 3000, 11750, 75000},
        {250, 950, 4500, 5850, 65000},
        {150, 1200, 3400, 12000, 58000}
    },
    // Wizard Monkey
    {
        {175, 450, 1450, 10000, 32000},
        {300, 800, 3300, 6000, 50000},
        {300, 300, 1500, 2800, 26500}
    },
    // Super Monkey
    {
        {2000, 2500, 20000, 100000, 500000},
        {1500, 1900, 7500, 25000, 70000},
        {3000, 1200, 5600, 55555, 165650}
    },
    // Ninja Monkey
    {
        {350, 350, 900, 2750, 35000},
        {250, 400, 1200, 5200, 22000},
        {300, 450, 2250, 5000, 40000}
    },
    // Alchemist
    {
        {250, 350, 1400, 2850, 48000},
        {250, 475, 2800, 4200, 45000},
        {650, 450, 1000, 2750, 40000}
    },
    // Druid
    {
        {350, 850, 1700, 4500, 60000},
        {250, 350, 1050, 4900, 35000},
        {100, 300, 600, 2350, 45000}
    },
    // Mermonkey
    {
        {250, 300, 1300, 4200, 23000},
        {300, 400, 2300, 8000, 52000},
        {200, 380, 2000, 7600, 25000}
    },
    // Banana Farm
    {
        {500, 600, 3000, 19000, 115000},
        {300, 800, 3650, 7200, 100000},
        {250, 400, 2700, 15000, 70000}
    },
    // Spike Factory
    {
        {800, 600, 2300, 9500, 125000},
        {600, 800, 2500, 7000, 41000},
        {150, 400, 1300, 3600, 30000}
    },
    // Monkey Village
    {
        {400, 1500, 800, 2500, 25000},
        {250, 2000, 7500, 20000, 40000},
        {500, 500, 10000, 3000, INVALID} // 5000} //monkey opolis is shit 
    },
    // Engineer Monkey
    {
        {500, 400, 575, 2500, 32000},
        {250, 350, 900, 13500, 72000},
        {450, 220, 450, 3600, 45000}
    },
    // Beast Handler
    {
        {160, 810, 2010, 12500, 45000},
        {175, 830, 2065, 9500, 60000},
        {190, 860, 2120, 9000, 30000}
    }
};

const int towerCosts[25] = {
    0,  // Hero
    200, // Dart Monkey
    315, // Boomerang Monkey
    375, // Bomb Shooter
    260, // Tack Shooter
    500, // Ice Monkey
    225, // Glue Gunner
    350, // Sniper Monkey
    325, // Monkey Sub
    400,// Monkey Buccaneer
    800,// Monkey Ace
    1500,// Heli Pilot
    750,// Mortar Monkey
    850,// Dartling Gunner
    250,// Wizard Monkey
    2500,// Super Monkey
    400,// Ninja Monkey
    550,// Alchemist
    400,// Druid
    475,// Mermonkey
    1250,// Banana Farm
    1000,// Spike Factory
    1200,// Monkey Village
    350,// Engineer Monkey
    250,// Beast Handler
};

const int te[25] {
    0, 
    1, // Dart Monkey
    2, // Boomerang Monkey
    3, // Bomb Shooter
    4, // Tack Shooter
    5, // Ice Monkey
    6, // Glue Gunner
    7, // Sniper Monkey
    8, // Monkey Sub
    9, // Monkey Buccaneer
    10, // Monkey Ace
    11, // Heli Pilot
    12, // Mortar Monkey
    13, // Dartling Gunner
    14, // Wizard Monkey
    15, // Super Monkey
    16, // Ninja Monkey
    17, // Alchemist
    18, // Druid
    19, // Mermonkey
    20, // Banana Farm
    21, // Spike Factory
    22, // Monkey Village
    23, // Engineer Monkey
    24  // Beast Handler 
};

const int towersAllowed[2] = {16, 17};

class Tower {
    private:
        int towerId; // which tower it is for upgrading
        int tower; 
        string towerTypeStr;
        int round_placed;
        int x, y;             // for placement
    public:
        
        int path[3];          // represent cross pathing
        

        Tower(int xPos, int yPos, int towerCode, int path0, int path1, int path2, int roundPlaced, int id)
            : towerTypeStr(towerMap[towerCode]), x(xPos), y(yPos), tower(towerCode),round_placed(roundPlaced), towerId(id)
        {
            path[0] = path0;
            path[1] = path1;
            path[2] = path2;
        }

        int getTowerType() {
            return tower;
        }

        int getTowerId() {
            return towerId;
        }

        int getRoundPlaced() {
            return round_placed;
        }

        string getTowerTypeStr() {
            return towerTypeStr;
        }
        
        int getX() {
            return x;
        }

        int getY() {
            return y;
        }
        

        string getCrossPathing() {
            return to_string(path[0]) + to_string(path[1]) + to_string(path[2]);
        }
};

struct Action {
    enum ActionType { PLACE, UPGRADE } type;
    Tower tower;
    int x, y;            // for placement
    int towerType, path; // Tower to represent tower type, path for top mid or bottom. Null for placing a tower.
    int round;
    int towerId; // which tower it is for upgrading
};

struct UpgradeOption {
    int towerId;
    int path;
    int cost;
    int tier;
    string towerTypeStr;
};

struct PlacementOption {
    int towerType;
    int cost;
    string towerTypeStr;

};

enum Difficulty { EASY, MEDIUM, HARD, IMPOPPABLE };

bool getInput() {
    char choice;
    cin >> choice;
    switch (choice) {
        case 't':
            return true;
        case 'f':
            return false;
        default:
            cout << "Invalid input. Please enter 't' or 'f'." << endl;
            return getInput();
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

        const int xMAx = 1000;
        const int yMax = 720;
        const int yMin = 40;
        const int xMin = 25;

        int startRound;
    public:
        StrategyMaker(int currentRound, Difficulty type) {
            TowersPlaced = {};
            StrategyActions = {};
            this->currentRound = currentRound;
            startRound = currentRound;
            totalTowers = 0;
            this->cash = 650; 

            this->type = type;
            switch (type) {
                case EASY:
                    cashMultiplier = 0.85;
                    break;
                case MEDIUM:
                    cashMultiplier = 1.0;
                    break;
                case HARD:
                    cashMultiplier = 1.08;
                    break;
                case IMPOPPABLE:
                    cashMultiplier = 1.2;
                    break;
            }
            
            mouseControl::initializeMouseControls();
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

        bool isValidBTD6Upgrade(const int path[3]) {
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

        vector<PlacementOption> getTowerPlacementOptions() {
            vector<PlacementOption> newTowers = {};
            for (auto& towerType : towersAllowed) {
                int cost = roundToNearest5(towerCosts[towerType], cashMultiplier);
                if (cost > cash) continue; // Skip if not enough cash
                if (towerType == 0) continue; // Skip hero (changes later)
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


        bool placeTower(int tower, int x, int y) {
            //implement mouse control later
            mouseControl::placeTower(tower, x, y);

            // check if placement was successful
            cout << "Tower placement at (" << x << ", " << y << ") for tower type " << towerMap[tower] << ". Was it successful? (t/f): ";
            bool success = getInput(); // manually tell ai if the placement was successful
            if (!success) {
                cerr << "Tower placement failed." << endl;
                return false; // Placement failed
            }
            Tower newTower( x, y, tower, 0, 0, 0, currentRound, totalTowers );
            totalTowers++;
            TowersPlaced.push_back(newTower);
            StrategyActions.push_back({Action::PLACE, newTower, x, y, tower, 0, currentRound, totalTowers});
            //cout << "Placed tower of type " << newTower.towerType << " at (" << x << ", " << y << ")" << endl;
            return true;
        }

        bool upgradeTower(int towerId, int path) {
            //implement mouse control later
            for (auto& tower : TowersPlaced) {
                if (tower.getTowerId() == towerId) {
                    tower.path[path]++; 
                    mouseControl::upgradeTower(tower.getX(), tower.getY(), path);
                    
                    int cost = roundToNearest5(towerUpgrades[tower.getTowerType()][path][tower.path[path]], cashMultiplier);
                    cash -= cost;
                    StrategyActions.push_back({Action::UPGRADE, tower, tower.getX(), tower.getY(), tower.getTowerType(), path, currentRound, towerId});

                    return true;
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
                StrategyFile << "Action Type: " << actionTypeToStr(action.type) << ", Tower ID: " << action.tower.getTowerId() << ", Position: (" << action.x << ", " << action.y << ")" << ", Tower Type: " << action.tower.getTowerTypeStr()  << ", Path: " << action.path  << ", Round: " << action.round  << endl;
            }
        }

                
        int getRandomInt    (int n1, int n2) {
            // srand(time(nullptr));  // seed (only once in main ideally)
            return n1 + rand() % (n2 - n1 + 1);
        }

        bool placeRandomTower(PlacementOption &selectedTower) {
            // 10 attempts to place a tower
            for (int i = 0; i < 10; i++) {
                    int x = getRandomInt(xMin, xMAx);
                    int y = getRandomInt(yMin, yMax);
                    if (placeTower(selectedTower.towerType, x, y)) {
                        cash -= selectedTower.cost;
                        cout << "Placed tower of type " << selectedTower.towerTypeStr << " at (" << x << ", " << y << ")" << endl;
                        return true;
                    } else {
                        cout << "Failed to place tower of type " << selectedTower.towerTypeStr << " at (" << x << ", " << y << ")" << endl;
                    }
                }
            return false; 
        }
        void singleRoundLoopAlgorithmOne() {
            
            
            while (true) {
            
                vector<PlacementOption> newTowers = getTowerPlacementOptions();
                if(newTowers.size() == 0) {
                    cout << "No towers available for placement." << endl;
                    break;
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
        

        void runGame() {
            bool gameOver = false;
            while (!gameOver) {
                singleRoundLoopAlgorithmOne();
                if (currentRound == startRound) {
                    mouseControl::ClickStartNextRound();
                    // click it twice for fast forward round 1 lmao
                }
                mouseControl::ClickStartNextRound();
                cout << "Waiting for next round..." << endl;
                cout << "Is the game over? (t/f): ";
                gameOver = getInput(); // manually tell ai if the game is over
                if (gameOver == true) {
                    cout << "Game Over!" << endl;
                    logStrategy();
                    logTowers();
                    break;
                }
                int temp;
                cout << "Enter the current cash: ";
                cin >> temp;
                this->cash = temp;
                incrementRound();
                cout << "Current round: " << currentRound << endl;
                
                
                cout << "Game is still ongoing." << endl;
            }
        }
};



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



int main() {
    // wait 2 seconds
    
    Sleep(2000);
    cout << "Script Started" << endl;
    StrategyMaker strategy(1, Difficulty::EASY);
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
    strategy.runGame();
    cout << "game has been finished" << endl;
    system("pause");
    return 0;
}
