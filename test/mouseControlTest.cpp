#include <iostream>
#include "../src/mouseControl/mouseControl.h"
#include <ctime>
#include <windows.h>
//impoppable mode on monkey meadows btw...
// g++ test/mouseControlTest.cpp src/mouseControl/mouseControl.cpp -o mouseControlTest.exe
// since it controls map you gotta like open the game yeah yeah bruh momentenoes

using namespace mouseControl;

void testPlaceAndUpgrade() {
    int x = 690;
    int y = 60;
    int topPath = 0;
    int botPath = 2;
    placeTower(1, x, y);
    upgradeTower(x, y, topPath);
    upgradeTower(x, y, botPath);

}

void testStartRound() {
    ClickStartNextRound();
    ClickStartNextRound();
}

void restartGame() {
    restartGameWhenOver(false);
}
int main() {
    initializeMouseControls();
    testPlaceAndUpgrade();
    testStartRound();
    Sleep(7000);
    restartGame();
    Sleep(200);
    placeTower(0, 690, 60);
    return 0;
}