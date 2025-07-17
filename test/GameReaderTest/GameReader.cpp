#include <iostream>
using namespace std;
#include <string>
#include "../../src/json.hpp"
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


json GameReader::readJsonFile() {
    //string dataPath = 

    // uses the goofy ahh file path that made in the constructor
    //"C:/Users/yanxi/Documents/Btd6Machine/Cpppractice/src/gameInfo/gameData.json";
    ifstream file(filePath);

    if (!file.is_open() || file.peek() == ifstream::traits_type::eof()) {
        cerr << "Error: Could not open or file empty: " << filePath << endl;
        return nullptr;
    }

    json gameDataJson;
    try {
        gameDataJson = json::parse(file);
    } catch (const nlohmann::json::parse_error& e) {
        cerr << "JSON Parse Error: " << e.what() << endl;
        return nullptr;
    }

    return gameDataJson;
}

void GameReader::updateValues() {
    json gameDataJson = readJsonFile();
    while (gameDataJson.is_null()) {
        Sleep(100);
        gameDataJson = readJsonFile();
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
    int iterations = 0;
    int maxIterations = 10;

    while (logNumber == prevLogNumber && iterations < maxIterations) {
        Sleep(100);
        iterations++;
        updateValues();
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
