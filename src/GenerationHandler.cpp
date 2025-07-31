#include "StrategyMaker.h"
#include "gameTypes.h"
#include "jsonHandlers/jsonManager.hpp"
#include "mouseControl/mouseControl.h"
#include<vector>
#include<string>
#include<windows.h>

using namespace std;
class GenerationHandler {
    private:
        int curGeneration = 0;
        
        JsonManager jsonManager;
        string filePathToGameData;
        Difficulty gameDifficulty;
        vector<int> towersAllowed;
        int roundsCutOffPerGeneration;
        int childrenPerGeneration;
        

        void loadSettings() {
            AlgorithmSettings settings = jsonManager.getAlgorithmSettingsFromJson();
            // loading settings ME WHEN i have SETTINGS to LOAD
            this->filePathToGameData = settings.filePathToGameData;
            this->gameDifficulty = settings.difficulty;
            // add param in constructor of strategy maker to allow towers
            this->towersAllowed = settings.towersAllowed;
            
            this->roundsCutOffPerGeneration = settings.roundsCutOffPerGeneration;
            this->childrenPerGeneration = settings.childrenPerGeneration;
            // copilot generate code to print all these out
            cout << "Loaded settings: " << endl;
            cout << "File Path to Game Data: " << filePathToGameData << endl << "Game Difficulty: " << gameDifficulty << endl;
            cout << "Towers Allowed: ";
            for (const auto& tower : towersAllowed) {
                cout << towerMap[tower] << ", ";
            }
            cout << endl << "Rounds Cut Off Per Generation: " << roundsCutOffPerGeneration << endl << "Children Per Generation: " << childrenPerGeneration << endl;
        }

        void loadUpgradesAndTowerCosts() {
            towerCosts = jsonManager.loadTowerCostsFromJson();
            towerUpgrades = jsonManager.loadTowerUpgradesFromJson();
            cout << "Loaded tower costs and upgrades." << endl;

        }

        int calculateScore(int endCash, int roundObtained) {
            // Calculate the score of the strategy based on the end cash and rounds completed
            int score = 0;
            
            // well we really only have two metrics to go off of and i think roundObtaiend is the most important out of the two.
            /* 
            Okay lets do a brainstorming
            Rounds must be either 1 < 101 
            but cash can be 0 < 178k BUT probably more 0 < 50k much more realistically
            since round will be the important metric, we need to scale these two variables down or up depending on their weight.
            OK so solution i got below, round is most important, but every 5k cash will mean an equal of +1 round
            What does this mean? lets say one of the strategies got to round 50 with 0 dollars when they died
            Now lets say another strategy got to round 48 with 17k left over, since 5k moneys is the equivalent to a round, the bottom one would be equivalent to one with 51 rounds and 2k cash
            now you see the ratio below, why is roundWeight 1k and each cash equial to 5k? why not reduce those?
            BECAUSE I WANT EVERYTHING IN INTEGER FORM GODDAMNIT
            */
           int RoundWeight = 1000;
           int HowMuchCashToWeighARound = 5000; 

           return (roundObtained * RoundWeight) + (endCash /  (HowMuchCashToWeighARound / RoundWeight));

        }
    
    public:
        GenerationHandler(int curGen = 0) 
        //: strategyMaker(gameDifficulty, filePathToGameData) 
        : curGeneration(curGen)
        {
            loadUpgradesAndTowerCosts();
            loadSettings();
            
        }

        Strategy formatStrategy(int endCash, int roundObtained, int childNumber, int generationNumber, vector<Action> &actions) {

            string ID = to_string(generationNumber) + "_" + to_string(childNumber);
            int score = calculateScore(endCash, roundObtained);
            Strategy strategy{ID, gameDifficulty, score, endCash, roundObtained, actions};

            // alright so if I ever get ANY BAD FUCKING RAM ACCESS AGAIN THIS FUNCTION HERE IS PROBABLY WHY <- here for when i debug 


            return strategy;
        }

        Strategy findBestStrategy(vector<Strategy> &strategy) {
            if (strategy.empty()) {
                throw std::invalid_argument("Strategy list is empty.");
            }
            int highestScoreFound = 0;
            Strategy *bestStratFoundSoFar = nullptr;
            for (auto &s : strategy) {
                if (s.score > highestScoreFound)  {
                    highestScoreFound = s.score;
                    bestStratFoundSoFar = &s;
                }
            }
            // again check THIS if there is any INVALID RAM ACCESSING
            return *bestStratFoundSoFar;
        }
        
        // params should be runGeneration(Strategy& parent) 
        Generation runGeneration() {
            vector<Strategy> childrenOfThisGeneration = {};
            childrenOfThisGeneration.reserve(childrenPerGeneration);
            cout << "runGeneration runs" << endl;

            // shit language because i accidentally did int i; instead if int i = 0; and wondered why shit wasnt working
            // intellisense do ur job :pray:
            for (int i = 0; i < childrenPerGeneration; ++i) {

                cout << "this is child: " << i << endl; // debug oh myt ruKicnF gOGODOWIUADOIJiawjfd
                StrategyMaker strategyGenerator(gameDifficulty, filePathToGameData, towersAllowed);
                vector<Action> actions = {}; //empty vector for now, also valid for when gen0
                GameResult rez = strategyGenerator.generateStrategy(actions);

                

                vector<Action> stratActionsObtained = strategyGenerator.getStrategyActions();
                int roundObtained = strategyGenerator.getCurrentRound();
                int endCash = strategyGenerator.getCash();
                // i stands for ith child of this generation btw btw btw btw..
                Strategy stratObtained = formatStrategy(endCash, roundObtained, i, curGeneration, stratActionsObtained);
                childrenOfThisGeneration.push_back(stratObtained);

                // fix for a more logic response this time pls and tank you
                if (rez == VICTORY) {
                    cout << "Victory Obtained yay" << endl;
                    jsonManager.writeToJson(stratObtained, "generations/winningStrategy.json");
                    // make it return the generation even though it hasnt had enough children im fucking lazy today (hi im lazy)
                } else {
                    cout << "restarting the game.." << endl;
                    Sleep(400);
                    strategyGenerator.restartGame();
                }
                
            }

            // make the remaining things into a helper function :ohhhhh:
            Strategy bestStrat = findBestStrategy(childrenOfThisGeneration);

            // placeholder "-1-0", -1
            // BUT THose two should be the parent strategy from the previous generation 
            // Basically -1 and -1 stand for the parents of the first gen, which ig stands for god??
            // not many people know this fun fact but I have a 10 minute youtube video i made when i was 15
            // about the halifax citadel on youtube which is the combination of Johnny Test SFX and justmehabibi replicated editing style
            Generation thisGen{curGeneration, "-1-0", -1, bestStrat.ID, bestStrat.score, childrenOfThisGeneration};
            //Generation thisGen{curGeneration, "-1-0", -1, "bestStrat.ID", 32, childrenOfThisGeneration};
            return thisGen;
        };

        // incomplete, pls finish another day kinda falling asleep here
        void mainControlLoop(int prevGen, Strategy &parentStrategy) {
            bool victoryFound = false; // temporary Fr this time
            int previousGeneration = prevGen;
            while (!victoryFound) {
                Generation gen = runGeneration();
                jsonManager.setGenFilePath(curGeneration);
                jsonManager.writeToJson(gen);
                previousGeneration = curGeneration;
                curGeneration++; // end of prev generation, so we increment to the next one
            }
            // mainControlLoop(previousGeneration, )
        }
        
};

// g++ src/GenerationHandler.cpp src/gameTypes.cpp src/StrategyMaker.cpp src/jsonHandlers/GameReader.cpp src/mouseControl/mouseControl.cpp -o ATestSetting/aitd6v3
int main() {

    GenerationHandler naturalSelection;
    // oh ym fcking god i forgot the ! sign so i was wondering why ts kept closing
    if (!mouseControl::initializeMouseControls()) {
        cout << "mouise control fails" << endl;
        system("pause");
        return 1;
    }
    JsonManager theOneAndOnlyWriter;
    system("pause");
    theOneAndOnlyWriter.setGenFilePath(0); // set the generation file path to generation 0
    // naturalSelection.runGeneration();
    theOneAndOnlyWriter.writeToJson(naturalSelection.runGeneration());
    system("pause");
    return 0;
}
