#include <iostream>
using namespace std;
#include <string>
#include "json.hpp"
#include <fstream>
#include <windows.h>
#include <string>
using json = nlohmann::json;

#include "gameReader.h"

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
    
    if ((towersPlaced == (prevTowerPlaced + 1))) {
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

    if (!file.is_open()) {
        std::cerr << "Error: Could not open JSON file at " << filePath << std::endl;
        // Optionally, you might want a small delay here before retrying in updateValues
        // Sleep(50); // Small delay before retrying file open
        return nullptr; // Indicate failure to open
    }

    // Check if the file is empty by checking its size
    // Move to end of file, get position, then reset to beginning
    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        std::cerr << "Warning: JSON file is empty at " << filePath << ". Retrying..." << std::endl;
        file.close();
        return nullptr; // Indicate an empty file, so updateValues can retry
    }
    file.seekg(0, ios::beg); // Reset file pointer to the beginning for parsing

    json gameDataJson;
    try {
        gameDataJson = json::parse(file);
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error (file likely empty or corrupt): " << e.what() << std::endl;
        file.close();
        return nullptr; // Indicate parse error, so updateValues can retry
    }

    file.close(); // Close the file after reading (important!)
    return gameDataJson;
}

void updateValues() {
    json gameDataJson = readJsonFile();
    while (gameDataJson.is_null()) {
        std::cerr << "Failed to read valid JSON. Retrying in 100ms..." << std::endl;
        Sleep(100); // Small delay before retrying to give other process time
        gameDataJson = readJsonFile();
    }
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
    int iterations = 0;
    int maxiterations = 10;
    
    // First, update values to get initial prevRound, prevLogNumber, etc.
    updateValues(); 
    //cout << "Current Log Number: " << logNumber << endl;
    //cout << "Previous Log Number: " << prevLogNumber << endl;
    // Now, enter the loop to wait for the log number to change.
    // We need to call updateValues *inside* the loop to refresh logNumber
    // and check against the prevLogNumber captured before the loop.
    while (logNumber == prevLogNumber) {
        //cout << "Waiting for log number to change..." << endl;
        iterations++;
        Sleep(80); // Sleep for 1 second before checking again
        if (iterations >= maxiterations) {
            // implementation later (due to level up)
            break; 
        }
        updateValues(); // Update values to check for a new logNumber
    }
    
}
bool soy = false;
namespace gameInfo {
    void initialize() {
        updateValues();
    }
    int getCash() {
        didLogFileChange();
        return cash;
    }

    int getStartRound() {
        return startRound;
    }

    int getCurRound() {
        didLogFileChange();
        return curRound;
    }

    int getLives() {
        return lives;
    }

    int getTowersPlaced() {
        didLogFileChange();
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

    

    bool didGameOver() {
        didLogFileChange();
        return isGameOver;

    }

    bool didGameWon() {
        didLogFileChange();
        return isGameWon;
    }
}

void testMetrics() {
        updateValues();
        cout << "Cash: " << cash << endl;
        cout << "Current Round: " << curRound << endl;
        cout << "Lives: " << lives << endl;
        cout << "Prev Towers Placed: " << prevTowerPlaced << endl;
        cout << "Towers Placed: " << towersPlaced << endl;
        cout << "Total Abilities: " << totalAbilities << endl;
        cout << "prev Log Number: " << prevLogNumber << endl;
        cout << "Log Number: " << logNumber << endl;
        cout << "Start Round: " << startRound << endl;
        cout << "Is Game Over: " << (isGameOver ? "Yes" : "No") << endl;
        cout << "Is Game Won: " << (isGameWon ? "Yes" : "No") << endl;
        Sleep(1000); // Sleep for 1 second before the next update 
}
void testmetrics2() {
    cout << "Cash: " << gameInfo::getCash() << endl;
        cout << "Towers placed:" << gameInfo::getTowersPlaced() << endl;
        cout << "Cur Round: " << gameInfo::getCurRound() << endl;
        Sleep(1000); // Sleep for 1 second before the next update 
}
/*
int main() {
    
    
   while (true) {
        
        cout << "is game over? " << (gameInfo::didGameOver() ? "Yes" : "No") << endl;
        cout << "is game won? " << (gameInfo::didGameWon() ? "Yes" : "No") << endl;
        Sleep(1000); // Sleep for 1 second before the next update
        
    
    }
    return 0;
}*/