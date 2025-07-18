#ifndef GAMEREADER_H
#define GAMEREADER_H

#include "../../src/json.hpp"
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

    // Private helper functions
    json readJsonFile();

    
    void updateValues();
    void didLogFileChange();

public:
    GameReader(const std::string& filePath);


    // Public interface
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
