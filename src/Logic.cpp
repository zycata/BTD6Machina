#include <iostream>
using namespace std;
#include <string>
#include "json.hpp"
#include <fstream>
#include <windows.h>
#include <string>
using json = nlohmann::json;

#include "Logic.h"
bool isGameOver = false;
bool isGameWon = false;
int cash = 0;
int curRound = 0;
int lives = 1;
int towersPlaced = 0;
int totalAbilities = 0;
int logNumber = 0;

int prevRound = 0;
int prevLogNumber = 0;
int prevTowerPlaced = 0;
int startRound = -1; // riyal or fakeh
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

json readJsonFile(){
    string filePath = "C:/Users/yanxi/Documents/Btd6Machine/Cpppractice/src/gameInfo/gameData.json";
    ifstream file(filePath);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open JSON file at " << filePath << std::endl;
        return nullptr;
        
    } else {
        cout << "File opened successfully at " << filePath << endl;
    }
    json gameDataJson = json::parse(file);
    file.close(); // Close the file after reading
    return gameDataJson;
}

void updateValues() {
    json gameDataJson = readJsonFile();
    while (gameDataJson.is_null()) {
        gameDataJson = readJsonFile();
        
    };
    prevRound = curRound;
    prevLogNumber = logNumber;
    prevTowerPlaced = towersPlaced;

    isGameOver = gameDataJson["isDefeated"];
    isGameWon = gameDataJson["gameWon"];
    cash = gameDataJson["Cash"]; //truncates towards zero (ignores decimal places)
    curRound = gameDataJson["Round"];
    lives = gameDataJson["Lives"];
    towersPlaced = gameDataJson["TowersPlaced"];
    totalAbilities = gameDataJson["TotalAbilities"];
    logNumber = gameDataJson["LogNumber"];
    startRound = gameDataJson["StartRound"];

    
}

void didLogFileChange() {
    while (logNumber == prevLogNumber) {
        updateValues();
        cout << "Waiting for log number to change..." << endl;
    };

      
}
namespace gameInfo {
    int getCash() {
        return cash;
    }

    int getStartRound() {
        return startRound;
    }

    int getCurRound() {
        return curRound;
    }

    int getLives() {
        return lives;
    }

    int getTowersPlaced() {
        return towersPlaced;
    }

    int getTotalAbilities() {
        return totalAbilities;
    }

    int getLogNumber() {
        return logNumber;
    }

    bool roundChanged() {
        didLogFileChange();
        return curRound != prevRound;
    }

    bool gameOver() {
        didLogFileChange();
        return isGameOver;

    }

    bool gameWon() {
        didLogFileChange();
        return isGameWon;
    }
}

int main() {
    /*
    assertBool(false, towerPlacedSuccessfully(), "Tower did not place successfully");
    towersPlaced++;
    assertBool(true, towerPlacedSuccessfully(), "Tower placed not successfully");*/
    while (true) {

        updateValues();
        cout << "Cash: " << cash << endl;
        cout << "Current Round: " << curRound << endl;
        cout << "Lives: " << lives << endl;
        cout << "Towers Placed: " << towersPlaced << endl;
        cout << "Total Abilities: " << totalAbilities << endl;
        cout << "Log Number: " << logNumber << endl;
        cout << "Start Round: " << startRound << endl;
        cout << "Is Game Over: " << (isGameOver ? "Yes" : "No") << endl;
        cout << "Is Game Won: " << (isGameWon ? "Yes" : "No") << endl;
        Sleep(1000); // Sleep for 1 second before the next update
    
    }
    return 0;
}