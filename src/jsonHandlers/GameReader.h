#pragma once

#ifndef GAMEREADER_H
#define GAMEREADER_H

#include <string>
#include "json.hpp"
using json = nlohmann::json;
class GameReader {
private:
    // All these variables must be declared here
    std::string filePath;

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
    int startRound = -1;
    std::vector<int> Abilities = {};
    // Private helper functions
    json readJsonFile();

    
    void updateValues();
    void didLogFileChange();

public:
    GameReader(const std::string& filePath);
    GameReader();

    // Public interface
    std::vector<int> getAbilities();
    void changeFilePath(const std::string& newPath);
    void initialize();
    int getCash();
    int getStartRound();
    int getCurRound();
    int getLives();
    int getTowersPlaced();
    int getTotalAbilities();
    int getLogNumber();
    bool roundChanged();
    bool didGameOver();
    bool didGameWon();

    // Your test functions
    void testMetrics();
    void testMetricsSimple();
};

#endif // GAMEREADER_H



// literally completely irrelevent but life fact I once saw some guy nervous before my linear algebra final and I
// thought it would be funny by asking him "whats a vector" before the exam was handed to cheer him up. However 
// just based on his reaction he looked like he was about to sewer slide himself after hearing that.
// exciting news.... 
