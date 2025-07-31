#include "../../src/jsonHandlers/jsonManager.hpp"



// g++ test/jsonHandlerTest/testWritingGenerations.cpp src/gameTypes.cpp -o test/jsonHandlerTest/testWritingGenerations

using namespace std;


void testWriteGeneration() {
    std::vector<Action> actions = {
        {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0},
        {Action::UPGRADE, nullptr, 0, 0, 0, 2, 7, 42},
        {Action::ABILITYUSE, nullptr, 0, 0, 0, 0, 10, 42}
    };
    
    Strategy strategy = {"6-9", HARD, 420, 650, 63, actions};
    Strategy strategyV2 = {"6-10", HARD, 32, 42, 422, actions}; 

    Generation generation6 = {6, "5-5", 5000, "6-9", 420, {strategy, strategyV2}};
    
    JsonManager jsonManager;
    jsonManager.setGenFilePath(6);
    jsonManager.writeGenerationToFile(generation6);
    
    Generation readGeneration = jsonManager.getFromJson<Generation>("generations/generation_6.json");
    assert(readGeneration.generationNumber == 6);
    assert(readGeneration.parentID == "5-5");
    assert(readGeneration.parentScore == 5000);
    assert(readGeneration.bestChildId == "6-9");
    assert(readGeneration.bestChildScore == 420);
    assert(readGeneration.children.size() == generation6.children.size());

    int curGenerationNumber = jsonManager.getCurrentGenerationNumber();
    assert(curGenerationNumber == 6);
    
    cout << "Generation test passed!" << endl;
}

int main() {
    cout << "Running JSON Handler Tests..." << endl;
    //testWriteGeneration();
    JsonManager jsonManager;
    int curGenerationNumber = jsonManager.getCurrentGenerationNumber();
    assert(curGenerationNumber == 0);
    
    cout << "All tests passed!" << endl;
    cin >> std::ws;
    return 0;
}