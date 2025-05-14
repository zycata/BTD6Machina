#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

int currentRound = 0;
int totalTowers = 0;

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


struct Action {
    enum ActionType { PLACE, UPGRADE } type;
    string towerType;
    int x, y;            // for placement
    int tower, path; // Tower to represent tower type, path for top mid or bottom. Null for placing a tower.
    int round;
    int towerId; // which tower it is for upgrading
};


class Tower {
public:
    string towerType;
    int x, y;             // for placement
    int tower;            // Tower to represent tower type, etc 1 to represent Dart Monkey
    int path[3];          // represent cross pathing
    int round_placed;
    int towerId;          // which tower it is for upgrading

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

    string getCrossPathing() {
        return to_string(path[0]) + to_string(path[1]) + to_string(path[2]);
    }
};



vector<Tower> TowersPlaced = {};
vector<Action> StrategyActions = {};



// Helper to convert ActionType to string
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

void logTowers() {
    ofstream TowerFile("logs/towersPlaced.txt");
    TowerFile << "Towers placed: " << TowersPlaced.size() << endl;
    cout << "Towers placed: " << TowersPlaced.size() << endl;

    for (auto& tower : TowersPlaced) {
        cout << "Tower ID: " << tower.towerId << ", Type: " << tower.towerType << ", Position: (" << tower.x << ", " << tower.y << ")" << ", Cross Pathing: " << tower.getCrossPathing() << endl;
        TowerFile << "Tower ID: " << tower.towerId << ", Type: " << tower.towerType << ", Position: (" << tower.x << ", " << tower.y << ")" << ", Cross Pathing: " << tower.getCrossPathing() << endl;
    }
}


int main() {
    cout << "Script Started" << endl;
    placeTower(1, 100, 200);
    placeTower(2, 300, 400);
    placeTower(3, 500, 600);
    logTowers();
    return 0;
}
