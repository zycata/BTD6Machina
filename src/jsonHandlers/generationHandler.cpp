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
// 
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
class generationHandler {
    private:
        const int soyamdendoija = 0; // shitpost
        
        

        

    public: 


        void writeStrategyJson(const Strategy& strategy) {
            json j_array = strategy;
            std::ofstream out_file("strategy.json");
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }
};



int main() {
    // Create a vector of sample Action objects
    std::vector<Action> actions = {
        {Action::PLACE, 10, 20, 1, -1, 5, 0},           // Placement action
        {Action::UPGRADE, 0, 0, 0, 2, 7, 42},           // Upgrade action
        {Action::ABILITYUSE, 0, 0, 0, 0, 10, 42}        // Ability use action
    };

    Strategy strategy = {"6-9", 420, 650, 63, actions};


    // Convert to JSON array
    json j_array = strategy;

    // Write to file
    std::ofstream out_file("strategy.json");
    if (out_file.is_open()) {
        out_file << j_array.dump(2); // Pretty print with 2-space indentation
        out_file.close();
    } else {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
        return 1;
    }

    return 0;
}