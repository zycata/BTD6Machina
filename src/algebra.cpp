#include <vector>
#include <iostream>
#include <string>
using namespace std;

int currentRound = 0;
int totalTowers = 0;
struct Action {
    enum ActionType { PLACE, UPGRADE } type;
    string towerType;
    int x, y;            // for placement
    int tower, path; // Tower to represent tower type, path for top mid or bottom. Null for placing a tower.
    int round;
    int towerId; // which tower it is for upgrading
};


struct Tower {
    string towerType;
    int x, y;            // for placement
    int tower;
    int path[3]; // represent cross Pathing

    int round_placed;
    int towerId; // which tower it is for upgrading
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
    Tower newTower = { "Cannon", x, y, tower, {0, 0, 0}, currentRound, totalTowers };
    totalTowers++;
    TowersPlaced.push_back(newTower);
    //cout << "Placed tower of type " << newTower.towerType << " at (" << x << ", " << y << ")" << endl;
    return true;
}

int main() {
    cout << "Script Started" << endl;
    placeTower(1, 100, 200);
    placeTower(2, 300, 400);
    placeTower(3, 500, 600);
    cout << "Towers placed: " << TowersPlaced.size() << endl;
    for (const auto& tower : TowersPlaced) {
        cout << "Tower ID: " << tower.towerId << ", Type: " << tower.towerType << ", Position: (" << tower.x << ", " << tower.y << ")" << endl;
    }
    return 0;
}
