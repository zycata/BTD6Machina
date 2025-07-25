#pragma once
#ifndef GAMETYPES_HPP
#define GAMETYPES_HPP

#include <string>
#include <vector>
#include <map>
#include <array>

std::map<int, std::string> towerMap = {
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
    {24, "Beast Handler"},
    {25, "Desperado"} //!!! implement desperado later plz
};



const int INVALID = -1;
std::vector<std::vector<std::vector<int>>> towerUpgrades = {
    
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
    },

    //Desperado
    {
        {250, 200, 1200, 5800, 17500},
        {150, 500, 3000, 8000, 42000},
        {220, 280, 2100, 9500, 31000}
    }
};

std::array<int, 26> towerCosts = {
    540,  // Hero
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
    300, // Desperado
};

// all towers temporarily not allowed for testing purposes lol
std::vector<int> te {
    0, //Hero
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
    24,  // Beast Handler 
    25 // Desperado
};

std::vector<int> towersAllowed = {0, 16, 17}; // only ninja monkey and alc atm + hero


class Tower {
    private:
        int towerId; // which tower it is for upgrading
        int tower; 
        std::string towerTypeStr;
        int round_placed;
        int x, y;             // for placement

        bool isValidBTD6Upgrade(std::array<int, 3> path) {
            int numUsedPaths = 0;
            int numHighPaths = 0;

            for (int i = 0; i < 3; ++i) {
                if (path[i] >= 6) return false;  // Can't go above tier 5
                if (path[i] > 0) ++numUsedPaths;
                if (path[i] >= 3) ++numHighPaths;
            }

            return numUsedPaths <= 2 && numHighPaths <= 1;
        }

    public:
        
        std::array<int, 3> path = {0,0,0};         // represent cross pathing
        

        Tower(int xPos, int yPos, int towerCode, int path0, int path1, int path2, int roundPlaced, int id)
            : towerTypeStr(towerMap[towerCode]), x(xPos), y(yPos), tower(towerCode),round_placed(roundPlaced), towerId(id)
        {
            path[0] = path0;
            path[1] = path1;
            path[2] = path2;
        }

        std::vector<int> getValidUpgradePaths() {
            std::vector<int> validPaths;
            for (int i = 0; i < 3; ++i) {
                std::array<int, 3> tempPath = path;
                tempPath[i] += 1; // Increment the path for upgrade
                if (isValidBTD6Upgrade(tempPath)) {
                    validPaths.push_back(i); // Add the path index if it's a valid upgrade
                }
            }
            return validPaths;
        }

        void upgradePath(int pathIndex) {
            if (pathIndex < 0 || pathIndex >= 3) {
                throw std::out_of_range("Invalid path index for upgrade");
            }
            if (path[pathIndex] < 5) { // Assuming max tier is 5
                path[pathIndex]++;
            } else {
                throw std::runtime_error("Cannot upgrade beyond tier 5");
            }
        }

        // returns towerCode for what type of tower it is (shit naming means i wrote this)
        int getTowerType() {
            return tower;
        }

        int getTowerId() {
            return towerId;
        }

        int getRoundPlaced() {
            return round_placed;
        }

        std::string getTowerTypeStr() {
            return towerTypeStr;
        }
        
        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        bool isHero() {
            return getTowerType() == 0;
        }
        
        //lowkey cosmetic purposes only ---------> trust me bro it'll be useful later trus trs....
        std::string getCrossPathing() {
            return std::to_string(path[0]) + std::to_string(path[1]) + std::to_string(path[2]);
        }
 
};


struct Action {
    enum ActionType { PLACE, UPGRADE, ABILITYUSE } type;
    // im gonna cry i act ually used a pointer im actually crying tears of happiness (THANK YOU FIRESHIP AND UR YT SHORTS FOR TEACHING TS)
    // wait but like unironically pointers are like kinda genius like... like this is genius wtf..... i mean other languages do ts for you but this is kinda cool im literally telling a rock what do
    // riyal or fakeh???
    Tower* tower; // ask for a pointer to tower lol
    int x, y;            // for placement
    int towerType; // Tower to represent tower type



    int path; // -1 if is a tower placement
    int round;
    int towerId; // which tower it is for upgrading
};



struct PlacementOption {
    int towerType;
    int cost;
    std::string towerTypeStr;

};

struct UpgradeOption {
    int towerId;
    int path;
    int cost;
    int tier;
    std::string towerTypeStr;
    bool isAllowed = true;
    bool isValid() const {
        return isAllowed && cost >= 0 && tier > 0;
    }
};

enum Difficulty { EASY, MEDIUM, HARD, IMPOPPABLE, CHIMPS };

enum GameResult { VICTORY, DEFEAT, OTHER}; //other for crash shit code etc
#endif 