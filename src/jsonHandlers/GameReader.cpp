#include <iostream>
using namespace std;
#include <string>
#include "json.hpp"
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;
using json = nlohmann::json;
#include "GameReader.h"




GameReader::GameReader(const std::string& path)
    : filePath(path)  // store the path
{
}

GameReader::GameReader()
    : filePath("")  // store the path
{
    cerr << "EMPTY PATH FILE" << endl;
}

json GameReader::readJsonFile(){
    ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open JSON file at " << filePath << std::endl;
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

void GameReader::updateValues() {
    json gameDataJson = readJsonFile();
    int maxAttempts = 10;
    int attempts = 0;
    // fun fact nasa code has to always have max attempts to do x or like an exit condition that has to hit, even tho true "while x" usually are coded with
    // the intent to run until it succeeds, and probably will, because of the nature of space exploration, they impose a max limit to prevent infinite loops from fuckass bugs idk
    // omg wait am i nasa coder nopw???
    
    while (gameDataJson.is_null() && attempts <= maxAttempts) {
        Sleep(100);
        std::cerr << "Failed to read valid JSON. Retrying in 100ms..." << std::endl;
        gameDataJson = readJsonFile();
        attempts++;
        
        if (attempts <= maxAttempts) {
            return;
        }
    }

    prevRound = curRound;
    prevLogNumber = logNumber;
    prevTowerPlaced = towersPlaced;

    isGameOver = gameDataJson["isDefeated"];
    isGameWon = gameDataJson["gameWon"];
    cash = gameDataJson["Cash"];
    curRound = gameDataJson["Round"];
    lives = gameDataJson["Lives"];
    towersPlaced = gameDataJson["TowersPlaced"];
    totalAbilities = gameDataJson["TotalAbilities"];
    logNumber = gameDataJson["LogNumber"];
    startRound = gameDataJson["StartRound"];
}

void GameReader::didLogFileChange() {
    updateValues();
    
    // 15 times 1.5 seconds to check right??? should be enuffs
    const int maxIterations = 15;
    int iterations = 0;

    while (logNumber == prevLogNumber && iterations < maxIterations) {
        Sleep(100);
        updateValues();
        iterations++;
    }

    // use this to get rtid of level up or something
    if (logNumber == prevLogNumber) {
        std::cerr << "Max attempts to read json file reached, returning previously found values" << std::endl;
    }
}


void GameReader::initialize() {
    updateValues();
}

void GameReader::changeFilePath(const std::string& newPath) {
    filePath = newPath;
};


int GameReader::getCash() {
    didLogFileChange();
    return cash;
}

int GameReader::getStartRound() {
    return startRound;
}

int GameReader::getCurRound() {
    didLogFileChange();
    return curRound;
}

int GameReader::getLives() {
    return lives;
}

int GameReader::getTowersPlaced() {
    didLogFileChange();
    return towersPlaced;
}

int GameReader::getTotalAbilities() {
    return totalAbilities;
}

int GameReader::getLogNumber() {
    return logNumber;
}

bool GameReader::roundChanged() {
    didLogFileChange();
    return curRound != prevRound;
}

bool GameReader::didGameOver() {
    didLogFileChange();
    return isGameOver;
}

bool GameReader::didGameWon() {
    return isGameWon;
}

void GameReader::testMetrics() {
    updateValues();
    cout << "Cash: " << cash << endl;
    cout << "Current Round: " << curRound << endl;
    cout << "Lives: " << lives << endl;
    cout << "Prev Towers Placed: " << prevTowerPlaced << endl;
    cout << "Towers Placed: " << towersPlaced << endl;
    cout << "Total Abilities: " << totalAbilities << endl;
    cout << "Prev Log Number: " << prevLogNumber << endl;
    cout << "Log Number: " << logNumber << endl;
    cout << "Start Round: " << startRound << endl;
    cout << "Is Game Over: " << (isGameOver ? "Yes" : "No") << endl;
    cout << "Is Game Won: " << (isGameWon ? "Yes" : "No") << endl;
    Sleep(1000);
}

void GameReader::testMetricsSimple() {
    cout << "Cash: " << getCash() << endl;
    cout << "Towers Placed: " << getTowersPlaced() << endl;
    cout << "Current Round: " << getCurRound() << endl;
    Sleep(1000);
}
