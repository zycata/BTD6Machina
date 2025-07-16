#include <iostream>


#include "../src/gameTypes.hpp"

using namespace std;
bool assertEquals(int expected, int actual, const string& message) {
    if (expected != actual) {
        cerr << "Assertion failed: " << message << " Expected: " << expected << ", Actual: " << actual << endl;
        return false;
    } else {
        cerr << "Test passed: " << message << endl;
    }
    return true;
}


int main() {
    PlacementOption option = {1, 100, "Dart Monkey"};
    cout << "Tower Type: " << option.towerType << endl;
    cout << "Cost: " << option.cost << endl;
    cout << "Tower Type String: " << option.towerTypeStr << endl;
    
    UpgradeOption upgrade = {1, 0, 200, 1, "Dart Monkey", true};
    cout << "Upgrade Tower ID: " << upgrade.towerId << endl;
    cout << "Upgrade Path: " << upgrade.path << endl;
    cout << "Upgrade Cost: " << upgrade.cost << endl;
    cout << "Upgrade Tier: " << upgrade.tier << endl;
    cout << "Upgrade Tower Type String: " << upgrade.towerTypeStr << endl;
    cout << "Is Upgrade Valid: " << (upgrade.isValid() ? "T" : "F") << endl;
}