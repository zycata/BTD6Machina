// gameTypes.h
#pragma once // Or #ifndef / #define / #endif guard, both are fine
#ifndef GAMETYPES_H
#define GAMETYPES_H

#include <string>
#include <vector>
#include <map>
#include <array>
#include <functional> // For std::function in Finalizer

// Forward declarations for classes/structs used as pointers or in other declarations
// This is good practice to minimize dependencies, though for simple structs like Action/UpgradeOption/PlacementOption,
// their full definitions are often needed if their members are directly accessed in other headers.
// For now, let's assume they are fully defined here as they are small and value-like.

// Enum Definitions (These are types and can be in headers)
enum Difficulty { EASY, MEDIUM, HARD, IMPOPPABLE, CHIMPS };
enum GameResult { VICTORY, DEFEAT, FINISHEDSTRATEGY, OTHER };

// Struct and Class Definitions (These define types and can be in headers)
class Tower {
private:
    int towerId; // which tower it is for upgrading
    int tower;
    std::string towerTypeStr;
    int round_placed;
    int x, y; // for placement

    bool isValidBTD6Upgrade(std::array<int, 3> path); // Declaration here, definition in .cpp or inline

public:
    std::array<int, 3> path = {0, 0, 0}; // represent cross pathing

    Tower(int xPos, int yPos, int towerCode, int path0, int path1, int path2, int roundPlaced, int id);

    std::vector<int> getValidUpgradePaths();
    void upgradePath(int pathIndex);
    int getTowerType();
    int getTowerId();
    int getRoundPlaced();
    std::string getTowerTypeStr();
    int getX();
    int getY();
    bool isHero();
    std::string getCrossPathing();
};

struct Action {
    enum ActionType { PLACE, UPGRADE, ABILITYUSE } type;
    Tower* tower; // ask for a pointer to tower lol
    int x, y; // for placement
    int towerType; // Tower to represent tower type
    int path; // -1 if is a tower placement
    int round;
    int towerId; // which tower it is for upgrading
    
};

struct PlacementOption {
    int towerType;
    int cost;
    std::string towerTypeStr;
};

struct UpgradeOption {
    int towerId;
    int path;
    int cost;
    int tier;
    std::string towerTypeStr;
    bool isAllowed = true; 
    bool isValid() const; 
};

// Finalizer struct (can be in header as it's a struct definition)
struct Finalizer {
    std::function<void()> func;
    ~Finalizer(); // Declaration, definition in .cpp
};


// Global Variable Declarations (using extern)
// These tell the compiler "this variable exists somewhere, but its definition is in another .cpp file."
extern std::map<int, std::string> towerMap;
extern std::vector<std::string> kTowerNames;
extern const int INVALID; // If it's a global const, extern is good
extern std::vector<std::vector<std::vector<int>>> towerUpgrades;
extern std::vector<int> towerCosts;


#endif // GAMETYPES_H