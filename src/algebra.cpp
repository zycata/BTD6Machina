#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;



map<int, std::string> towerMap = {
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

const int towerUpgrades[24][3][5] = {
    
    {

        {0, 0, 0, 0, 0}, // Hero
        {0, 0, 0, 0, 0}, // Path 1
        {0, 0, 0, 0, 0}  // Path 2
    },

    // Dart Monkey
    {
        {140, 220, 300, 1800, 15000}, // Path 1
        {100, 190, 400, 7500, 45000}, // Path 2
        {90, 200, 450, 1800, 18000}   // Path 3
    },
    // Boomerang Monkey
    {
        {150, 300, 750, 3000, 25000},
        {130, 270, 700, 2800, 23000},
        {140, 290, 720, 2900, 24000}
    },
    // Bomb Shooter
    {
        {200, 400, 1000, 4000, 30000},
        {180, 360, 900, 3600, 28000},
        {190, 380, 950, 3800, 29000}
    },
    // Tack Shooter
    {
        {100, 200, 500, 2000, 20000},
        {110, 220, 550, 2200, 21000},
        {120, 240, 600, 2400, 22000}
    },
    // Ice Monkey
    {
        {150, 300, 750, 3000, 25000},
        {160, 320, 800, 3200, 26000},
        {170, 340, 850, 3400, 27000}
    },
    // Glue Gunner
    {
        {100, 200, 500, 2000, 20000},
        {110, 220, 550, 2200, 21000},
        {120, 240, 600, 2400, 22000}
    },
    // Sniper Monkey
    {
        {250, 500, 1250, 5000, 35000},
        {260, 520, 1300, 5200, 36000},
        {270, 540, 1350, 5400, 37000}
    },
    // Monkey Sub
    {
        {300, 600, 1500, 6000, 40000},
        {310, 620, 1550, 6200, 41000},
        {320, 640, 1600, 6400, 42000}
    },
    // Monkey Buccaneer
    {
        {350, 700, 1750, 7000, 45000},
        {360, 720, 1800, 7200, 46000},
        {370, 740, 1850, 7400, 47000}
    },
    // Monkey Ace
    {
        {400, 800, 2000, 8000, 50000},
        {410, 820, 2050, 8200, 51000},
        {420, 840, 2100, 8400, 52000}
    },
    // Heli Pilot
    {
        {450, 900, 2250, 9000, 55000},
        {460, 920, 2300, 9200, 56000},
        {470, 940, 2350, 9400, 57000}
    },
    // Mortar Monkey
    {
        {500, 1000, 2500, 10000, 60000},
        {510, 1020, 2550, 10200, 61000},
        {520, 1040, 2600, 10400, 62000}
    },
    // Dartling Gunner
    {
        {550, 1100, 2750, 11000, 65000},
        {560, 1120, 2800, 11200, 66000},
        {570, 1140, 2850, 11400, 67000}
    },
    // Wizard Monkey
    {
        {600, 1200, 3000, 12000, 70000},
        {610, 1220, 3050, 12200, 71000},
        {620, 1240, 3100, 12400, 72000}
    },
    // Super Monkey
    {
        {1000, 2000, 5000, 20000, 100000},
        {1100, 2200, 5500, 22000, 110000},
        {1200, 2400, 6000, 24000, 120000}
    },
    // Ninja Monkey
    {
        {650, 1300, 3250, 13000, 75000},
        {660, 1320, 3300, 13200, 76000},
        {670, 1340, 3350, 13400, 77000}
    },
    // Alchemist
    {
        {700, 1400, 3500, 14000, 80000},
        {710, 1420, 3550, 14200, 81000},
        {720, 1440, 3600, 14400, 82000}
    },
    // Druid
    {
        {750, 1500, 3750, 15000, 85000},
        {760, 1520, 3800, 15200, 86000},
        {770, 1540, 3850, 15400, 87000}
    },
    // Mermonkey
    {
        {750, 1500, 3750, 15000, 85000},
        {760, 1520, 3800, 15200, 86000},
        {770, 1540, 3850, 15400, 87000}
    },
    // Banana Farm
    {
        {800, 1600, 4000, 16000, 90000},
        {810, 1620, 4050, 16200, 91000},
        {820, 1640, 4100, 16400, 92000}
    },
    // Spike Factory
    {
        {850, 1700, 4250, 17000, 95000},
        {860, 1720, 4300, 17200, 96000},
        {870, 1740, 4350, 17400, 97000}
    },
    // Monkey Village
    {
        {900, 1800, 4500, 18000, 100000},
        {910, 1820, 4550, 18200, 101000},
        {920, 1840, 4600, 18400, 102000}
    },
    // Engineer Monkey
    {
        {950, 1900, 4750, 19000, 105000},
        {960, 1920, 4800, 19200, 106000},
        {970, 1940, 4850, 19400, 107000}
    }
};



class Tower {
    private:
        int towerId; // which tower it is for upgrading
        int tower; 
    public:
        string towerType;
        int x, y;             // for placement
        int path[3];          // represent cross pathing
        int round_placed;

        Tower(int xPos, int yPos, int towerCode,
            int path0, int path1, int path2,
            int roundPlaced, int id)
            : towerType(towerMap[towerCode]), x(xPos), y(yPos), tower(towerCode),
            round_placed(roundPlaced), towerId(id)
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
    string towerType;
};

class StrategyMaker {
    private:
        vector<Tower> TowersPlaced;
        vector<Action> StrategyActions;
        int currentRound;
        int totalTowers;
        int cash;
    public:
        

        StrategyMaker(int currentRound) {

            TowersPlaced = {};
            StrategyActions = {};
            this->currentRound = currentRound;
            totalTowers = 0;
            this->cash = 1000000; 
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



        vector<UpgradeOption> getAvailableUpgrades() {
            vector<UpgradeOption> availableUpgrades;
            for (auto& tower : TowersPlaced) {
                for (int i = 0; i < 3; i++) {
                    int cost = towerUpgrades[tower.getTowerType()][i][tower.path[i]];

                    tower.path[i] += 1;
                    if (isValidBTD6Upgrade(tower.path) && cost <= cash ) {
                        UpgradeOption option;
                        option.towerId = tower.getTowerId();
                        option.path = i;
                        option.cost = cost;
                        option.tier = tower.path[i];
                        option.towerType = tower.towerType;
                        availableUpgrades.push_back(option);

                    } 
                    tower.path[i] -= 1; // Reset the path for the next iteration
                }
            }
            return availableUpgrades;
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
            Tower newTower( x, y, tower, 0, 0, 0, currentRound, totalTowers );
            totalTowers++;
            TowersPlaced.push_back(newTower);
            //cout << "Placed tower of type " << newTower.towerType << " at (" << x << ", " << y << ")" << endl;
            return true;
        }

        bool upgradeTower(int towerId, int path) {
            //implement mouse control later
            for (auto& tower : TowersPlaced) {
                if (tower.getTowerId() == towerId) {
                    tower.path[path]++; // Set the path to 1 to indicate it's upgraded
                    // mouse::upgradeTower(tower.x, tower.y, path);
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
                cout << "Tower ID: " << tower.getTowerId() << ", Type: " << tower.towerType << ", Position: (" << tower.x << ", " << tower.y << ")" << ", Cross Pathing: " << tower.getCrossPathing() << ", Round Placed: " << tower.round_placed << endl;
                TowerFile << "Tower ID: " << tower.getTowerId() << ", Type: " << tower.towerType << ", Position: (" << tower.x << ", " << tower.y << ")" << ", Cross Pathing: " << tower.getCrossPathing() << ", Round Placed: " << tower.round_placed << endl;
            }
        }

};



void printAvailableUpgrades(const vector<UpgradeOption>& upgrades) {
    cout << "Available Upgrades:" << endl;
    for (const auto& upgrade : upgrades) {
        cout << "Tower Type: " << upgrade.towerType << ", Tower ID: " << upgrade.towerId << ", Path: " << upgrade.path << ", Upgrade Tier: " << upgrade.tier << ", Cost: " << upgrade.cost << endl;
    }
}


int main() {
    cout << "Script Started" << endl;
    StrategyMaker strategy(6);
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
    int x = 0;
    cin >> x;

    cout << x*3 << endl;
    system("pause");
    return 0;
}
