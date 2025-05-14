#include <iostream>
using namespace std;
#include <string>


int towersPlaced = 0;
int prevTowerPlaced = 0;

bool towerPlacedSuccessfully() {
    if (towersPlaced == (prevTowerPlaced + 1)) {
        prevTowerPlaced++;
        return true;
    }
    return false;
}


bool assertBool(bool expected ,bool condition, string message) {
    if (condition != expected) {
        cerr << "Assertion failed: " << message << endl;
        return false;
    } else {
        cerr << "Test passed" << endl;
    }
    return true;
}

int main() {

    assertBool(false, towerPlacedSuccessfully(), "Tower did not place successfully");
    towersPlaced++;
    assertBool(true, towerPlacedSuccessfully(), "Tower placed not successfully");
    return 0;
}