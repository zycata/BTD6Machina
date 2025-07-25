
#include "../../src/jsonHandlers/jsonManager.hpp"

// me when writing tests, like lowkey code should just work like if i was good enuff "cries in c++" wait wtf this isn't c++ exclusive
// would it not be kinda funny writing a fanfiction about c++ having sex with java and having oop shoved even more up my ass
using namespace std;


void testWritingActions() {
    Action action = {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0};
    JsonManager jsonManager;
    jsonManager.writeToJson(action, "jsonHandlerTest/action.json");
    Action readAction = jsonManager.getFromJson<Action>("jsonHandlerTest/action.json");
    assert(readAction.type == Action::PLACE);
    assert(readAction.x == 10);
    assert(readAction.y == 20);
    assert(readAction.towerType == 1);
    assert(readAction.path == -1);
    cout << "Action test passed!" << endl;  
}

void testWritingStrategy() {
    std::vector<Action> actions = {
        {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0},
        {Action::UPGRADE, nullptr, 0, 0, 0, 2, 7, 42},
        {Action::ABILITYUSE, nullptr, 0, 0, 0, 0, 10, 42}
    };
    
    Strategy strategy = {"6-9", HARD, 420, 650, 63, actions};
    JsonManager jsonManager;
    jsonManager.writeToJson(strategy, "jsonHandlerTest/strategy.json");
    
    Strategy readStrategy = jsonManager.getFromJson<Strategy>("jsonHandlerTest/strategy.json");
    assert(readStrategy.ID == "6-9");
    assert(readStrategy.difficulty == HARD);
    assert(readStrategy.score == 420);
    assert(readStrategy.endCash == 650);
    assert(readStrategy.roundObtained == 63);
    assert(readStrategy.actions.size() == actions.size());
    cout << "Strategy test passed!" << endl;
}

void testWritingGeneration() {
    std::vector<Action> actions = {
        {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0},
        {Action::UPGRADE, nullptr, 0, 0, 0, 2, 7, 42},
        {Action::ABILITYUSE, nullptr, 0, 0, 0, 0, 10, 42}
    };
    
    Strategy strategy = {"6-9", HARD, 420, 650, 63, actions};
    Strategy strategyV2 = {"6-10", HARD, 32, 42, 422, actions}; 

    Generation generation6 = {6, "5-5", 5000, "6-9", 420, {strategy, strategyV2}};
    
    JsonManager jsonManager;
    jsonManager.writeToJson(generation6, "jsonHandlerTest/generation_6.json");
    
    Generation readGeneration = jsonManager.getFromJson<Generation>("jsonHandlerTest/generation_6.json");
    assert(readGeneration.generationNumber == 6);
    assert(readGeneration.parentID == "5-5");
    assert(readGeneration.parentScore == 5000);
    assert(readGeneration.bestChildId == "6-9");
    assert(readGeneration.children.size() == generation6.children.size());
    cout << "Generation test passed!" << endl;
}

// I mean assert is cool but i think the shitty assertequals function i made is cool (i think im slick)
// i like i usually don't gravitate towards rap songs, but 1-800 by bbno$ is actually fire wtf....
// let me 1-800 blow your mind!! with this projet 

void testMisc() {
    JsonManager manHandler;
    manHandler.setGenFilePath(6);
    assert(manHandler.getGenFilePath() == "generations/generation_6.json");
    cout << "Misc test passed!" << endl;
}
void testJsonManager() {
    testWritingActions();
    testWritingStrategy();
    testWritingGeneration();
}

void testLoadingBaseCostsFromJson() {
    JsonManager jsonManager;
    std::array<int, 26> testCosts = jsonManager.loadTowerCostsFromJson("config/tower_costs.json");
    cout << "Hero Cost: " << testCosts[0] << endl; // Print Hero cost for verification
    assert(testCosts.size() == 26); // Ensure the array size is correct
    assert(testCosts[0] == 540); // Hero
    
    assert(testCosts[1] == 200); // Dart Monkey
    assert(testCosts[2] == 315); // Boomerang Monkey
    assert(testCosts[3] == 375); // Bomb Shooter
    cout << "Loading from JSON test passed!" << endl;
}

void testLoadingFromJsonUpgrades() {
    JsonManager jsonManager;
    // Test loading tower upgrades from JSON
    cout << "Loading tower upgrades from JSON..." << endl;
    std::vector<std::vector<std::vector<int>>> testUpgrades = jsonManager.loadTowerUpgradesFromJson("config/tower_upgrades.json");
    assert(testUpgrades.size() == 26);
    /*
    cout << "Tower upgrades loaded successfully!" << endl;
    cout << "Test upgrades size: " << testUpgrades.size() << endl;
    cout << "Test dart path 1 tier 1: " << testUpgrades[1][0][0] << endl; // Dart Monkey Path 1 Tier 1 */
    assert(testUpgrades[0][0][0] == -1); // Hero upgrades should be -1
    assert(testUpgrades[1][0][0] == 140); // Dart Monkey Path 1 Tier 1
    assert(testUpgrades[25][2][4] == 31000); // Desperado PAth 3 tier 5
    cout << "Loading tower upgrades from JSON test passed!" << endl;
}

void testLoadingSettings() {
    JsonManager jsonManager;
    AlgorithmSettings settings = jsonManager.getAlgorithmSettingsFromJson("config/settings.json");
    
    assert(settings.filePathToGameData == "C:/Games/MyGame/ExamplePath.json");
    assert(settings.difficulty == HARD);
    assert(settings.towersAllowed.size() == 3); // Assuming 3 towers are allowed
    assert(settings.roundsCutOffPerGeneration == 5);
    assert(settings.childrenPerGeneration == 10);

    std::vector<int> expectedTowersAllowed = {0, 16, 17}; // Hero, Ninja Monkey, Alchemist
    assert(settings.towersAllowed == expectedTowersAllowed);
    
    cout << "Algorithm settings test passed!" << endl;
}
void runAllTests() {
    cout << "Running JSON Handler Tests..." << endl;
    testJsonManager();
    testMisc();
    testLoadingBaseCostsFromJson();
    testLoadingFromJsonUpgrades();
    cout << "All tests passed!" << std::endl;
}
int main() {
    
    testLoadingSettings();
    runAllTests();
    return 0;
}