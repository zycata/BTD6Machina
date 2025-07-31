#pragma once

#ifndef STRATEGYMAKER_H
#define STRATEGYMAKER_H

#include <vector>
#include <string>
#include <array> // For std::array
#include "gameTypes.h"
#include "jsonHandlers/GameReader.h"


// Forward declarations of structs/enums from gameTypes.hpp
// Assuming these are defined in gameTypes.hpp and are necessary for StrategyMaker.h

class StrategyMaker {
private:
    std::vector<Tower> TowersPlaced;
    std::vector<Action> StrategyActions;
    int currentRound;
    int totalTowers;
    int cash;
    Difficulty type;
    int towerIdCounter; // Counter for unique tower IDs
    float cashMultiplier;
    std::vector<int> towersAllowed;
    GameReader gameInfo;

    const int xMAx = 1000;
    const int yMax = 720;
    const int yMin = 40;
    const int xMin = 25;

    int startRound;
    const UpgradeOption emptyUpgrade; // Empty upgrade option to return when no upgrades are available

    bool isHeroAlreadyPlaced();
    void logTowers();
    void logStrategy();

public:
    StrategyMaker(Difficulty type, std::string filePath, std::vector<int> towersAllowed);

    // Using a struct for cleanup, similar to how RAII works for resources
    // This will ensure logItems() is called when StrategyMaker goes out of scope
    struct Finalizer {
        std::function<void()> cleanup;
        Finalizer(std::function<void()> fn) : cleanup(fn) {}
        ~Finalizer() { cleanup(); }
    };


    void logItems();
    void setCash(int cash);
    int getCash();
    int getCurrentRound();
    void incrementRound();
    std::vector<Tower> getTowersPlaced();
    std::vector<Action> getStrategyActions();
    bool isValidBTD6Upgrade(std::array<int, 3> path);
    int roundToNearest5(int num, float multiplier);

    //refactor soon
    std::vector<UpgradeOption> getLegalUpgrades();
    std::vector<UpgradeOption> getAvailableUpgrades();
    std::vector<PlacementOption> getTowerPlacementOptions();
    const char* actionTypeToStr(Action::ActionType type);
    bool checkIfSuccessfullyPlaced();
    bool placeTower(int towerCode, int x, int y);

    // TODO --> MAKE IT SO IT A TOWER ID IS FOUND TO HAVE FAILED ENOUGH TIMES MAKE IT SO THAT IT DELETES IT OFF (FAILED TO PLACETHE TOWER WHEN THOUGHT IT DID)
    // towers failing to place and the codfe thinking it placed is pretty rare but it's happened (enough times) where im making ts (or fixin gplace towers idk)
    // then goes to towers and strategy actions and deletes the tower (REMOVES IT SMITES IT YEET YEET)
    // will also need a new system to ID towers after that but das easy (j'espere)
    bool upgradeTower(int towerId, int path);


    // n2 > n1
    // returns random int [n1, n2] (includes n1 and n2)
    int getRandomInt(int n1, int n2);

    // places a random tower... tries 5 times to place it before trying a new tower or giving up lmao
    bool placeRandomTower(PlacementOption &selectedTower);

    // pretty much places at most 5 towers randomly, but only if the towers are affordable immediately.
    void placementAlgorithmOne();

    void upgradeAlgorithmOne();

    void singleRoundLoopAlgorithmOne();

    // function that selects an up grade for a tower --> only runs for higherRounds
    // returns an upgrade option however it doesn't check if player has enough cash allowing the ai to "save up" for a tier 5 or something
    // assuming it chooses an upgrade that the ai can afford on the spot, it'll just purchase it and buy it then run again or choose something else to run yes???
    // AMONGLA SWAG pls work on this and lock in
    UpgradeOption getTargetUpgrade();

    // remember to add chedk if it returns a valid upgrade
    // add something to reason with the price lmao yes true true amongla swag....
    UpgradeOption upgradeAlgorithmTwo();

    bool didRoundEnd();
    void startNextRound();

    // !!! TODO: make shitty ai restart the game using the restart button thing when the game is over
    // TODO:
    GameResult runGame();

    /* Okay let me think of a design process here
    basically it receives a vector of actions, and executes them in order pretty much,
    so lets start, since this must always be called right as the game starts, we can start by checking if
    the round is active.
    -> isroundactive? -> if true -> wait
    -> if false -> increment the vectors -> is action current round? -> yes? -> continue
    -> if no then wait for next round, check again

    hey that wasn't too bad, also used a pointer because i think im so cool
    so glad no need to allocate heap i could never :sob:
    */

    // TODO: this has overlap with the previous function, so maybe make a helper or combine these two?
    // should be possible for sure, anyways im done for the day tommorow for file gen with jsonManager finally
    GameResult followStrategy(std::vector<Action>& childrenStrategy);

    GameResult generateStrategy(std::vector<Action>& childrenStrategy);

    // TODO: MAKE THIS CHECK IF IT"S THE START ROUND AND MODE IS CHIMPS
    void restartGame();
};

#endif // STRATEGYMAKER_H