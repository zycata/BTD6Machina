#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include "json.hpp"
//#include "../gameTypes.hpp"


using json = nlohmann::json;

struct Action {
    enum ActionType { PLACE, UPGRADE, ABILITYUSE } type;
    int x, y;            // for placement
    int towerType; // Tower to represent tower type
    // Tower tower; // should still work when uncommented 


    int path; // -1 if is a tower placement
    int round;
    int towerId; // which tower it is for upgrading
};


struct Strategy {
    
    std::string ID;
    int score;
    int endCash; 
    int roundObtained;
    std::vector<Action> actions;

};  

struct Generation {
    int generationNumber;
    std::string parentID;
    int parentScore;

    std::string bestChildId;
    int bestChildScore;
    std::vector<Strategy> children;


};

std::string to_string(Action::ActionType type) {
    switch (type) {
        case Action::PLACE: return "PLACE";
        case Action::UPGRADE: return "UPGRADE";
        case Action::ABILITYUSE: return "ABILITYUSE";
        default: return "UNKNOWN";
    }
}

void to_json(json& j, const Action& action) {
    j = json{
        {"type", to_string(action.type)},
        {"x", action.x},
        {"y", action.y},
        {"towerType", action.towerType},
        {"path", action.path},
        {"round", action.round},
        {"towerId", action.towerId}
    };
}

// OMG IM ATUALLY USING FUNCTION OVERLOADING  
void to_json(json& j, const Strategy& strategy) {
    json actions = strategy.actions;
    j = json{
        {"ID", strategy.ID},
        {"score", strategy.score},
        {"endCash", strategy.endCash},
        {"roundObtained", strategy.roundObtained},
        {"actions", actions}
    };
}

// function overloading for a third time??? so real....
// I mean i guess now I know when functinon overloading will actually be used..
// soy admen
void to_json(json& j, const Generation& generation) {
    json children = generation.children;
    j["generationNumber"] = generation.generationNumber;
    j["parentID"] = generation.parentID;
    j["ParentScore"] = generation.parentScore;
    j["bestChildId"] = generation.bestChildId;
    j["children"] = children;
    // mewhen children...
}

class generationHandler {
    
    private:
        const int soyamdendoija = 0; // shitpost
        std::string filePath;
    public: 

        void setGenFilePath(int generationNumber) {
            std::string generationNumberString = std::to_string(generationNumber);
            filePath = "generation_" + generationNumberString + ".json";
            
        }

        void writeStrategyToJson(const Strategy& strategy) {
            json j_array = strategy;
            std::ofstream out_file("strategy.json");
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }

        void writeGenerationToJson(const Generation& generation) {
            json j_array = generation;
            std::ofstream out_file(filePath);
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }
};



int main() {
    
    std::vector<Action> actions = {
        {Action::PLACE, 10, 20, 1, -1, 5, 0},         
        {Action::UPGRADE, 0, 0, 0, 2, 7, 42},          
        {Action::ABILITYUSE, 0, 0, 0, 0, 10, 42}       
    };

    Strategy strategy = {"6-9", 420, 650, 63, actions};

    Strategy strategyV2 = {"6-10", 32, 42, 422, actions}; 

    Generation generation6 = {6, "5-5", 5000, "6-9", 420, {strategy, strategyV2}};

    generationHandler manHandler;
    manHandler.setGenFilePath(6); // for generation 6

    manHandler.writeGenerationToJson(generation6);

    return 0;
}