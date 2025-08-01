
#include "StrategyMaker.h"

#include<iostream>
using namespace std;
#include "mouseControl/mouseControl.h"
#include<Windows.h>
#include<vector>
#include"jsonHandlers/jsonManager.hpp"

//g++ src/test.cpp src/gameTypes.cpp src/StrategyMaker.cpp src/jsonHandlers/GameReader.cpp src/mouseControl/mouseControl.cpp -o ATestSetting/aitd6v2
// TO compile with the SICKASS icon use:
// g++ src/test.cpp src/gameTypes.cpp src/StrategyMaker.cpp src/jsonHandlers/GameReader.cpp src/mouseControl/mouseControl.cpp resource.o -o ATestSetting/aitd6v2
// use below to link libraries (when i release ts eventually)
// g++ src/test.cpp src/gameTypes.cpp src/StrategyMaker.cpp src/jsonHandlers/GameReader.cpp src/mouseControl/mouseControl.cpp resource.o -static -o ATestSetting/aitd6v2
void testingriyal() {
    string filePath = "D:/Gamesfiles/Steam/steamapps/common/BloonsTD6/gameData/gameData.json";
    cout << "Script Started" << endl;

    if(!mouseControl::initializeMouseControls()) {
        system("pause");
        return;
    }
    system("pause");
    //Sleep(1000); // wait for the game to load   


    
    vector<int> towersAllowed = {0, 1, 2, 16, 17, 15};
    StrategyMaker strategy(Difficulty::EASY, filePath, towersAllowed);
    
    Sleep(1000);

    strategy.restartGame();
    system("pause");
    // lets give it a sample stratgegy to follow, dart then ice then bombaclat
    vector<Action> testChildStrategy = {
        {Action::PLACE, nullptr, 100, 250, 1, -1, 1, 1},
        {Action::UPGRADE, nullptr, 100, 250, 1, 0, 1, 1},
        {Action::PLACE, nullptr, 300, 400, 5, -1, 3, 2},
        {Action::UPGRADE, nullptr, 300, 400, 5, 2, 3, 2},
        {Action::PLACE, nullptr, 200, 400, 3, -1, 5, 3}

    };
    strategy.generateStrategy(testChildStrategy);

    cout << "Strategy executed successfully." << endl;
}

int main() {
    cout << "hey so this thing works btw it compiled" << endl;
    
    system("pause");
    testingriyal();
    system("pause");
    return 0;
}