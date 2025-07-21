#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include "json.hpp"
#include "../gameTypes.hpp"


using json = nlohmann::json;



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


// gonna use function overloading for another function?? TS cannort be real
void from_json(const json& j, Action& action) {
    std::string type_str = j.at("type").get<std::string>();
    if (type_str == "PLACE") action.type = Action::PLACE;
    else if (type_str == "UPGRADE") action.type = Action::UPGRADE;
    else if (type_str == "ABILITYUSE") action.type = Action::ABILITYUSE;
    else throw std::runtime_error("Invalid type: " + type_str);

    j.at("x").get_to(action.x);
    j.at("y").get_to(action.y);
    j.at("towerType").get_to(action.towerType);

    j.at("path").get_to(action.path);
    j.at("round").get_to(action.round);
    j.at("towerId").get_to(action.towerId);

}


class generationHandler {
    
    private:
        const int soyamdendoija = 0; // shitpost

        std::string filePath;
        json readActionFromJson() {
            std::ifstream file("action.json");
            if (!file.is_open()) {
                std::cerr << "Error: Could not open JSON file at " << filePath << std::endl;
                Sleep(50); // Small delay before retrying file open
                return nullptr; // Indicate failure to open
            }
            file.seekg(0, ios::end);
            if (file.tellg() == 0) {
                std::cerr << "Warning: JSON file is empty at " << filePath << ". Retrying..." << std::endl;
                file.close();
                return nullptr; // Indicate an empty file, so updateValues can retry
            }
            file.seekg(0, ios::beg); // Reset file pointer to the beginning for parsing

            json actionJson;
            try {
                actionJson = json::parse(file);
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "JSON Parse Error (file likely empty or corrupt): " << e.what() << std::endl;
                file.close();
                return nullptr; // Indicate parse error, so updateValues can retry
            }

            file.close(); // Close the file after reading (important!)
            return actionJson;

        }



    public: 

        void setGenFilePath(int generationNumber) {
            std::string generationNumberString = std::to_string(generationNumber);
            filePath = "generation_" + generationNumberString + ".json";
            
        }

        void writeActionToJson(const Action& action) {
            json j_array = action;
            std::ofstream out_file("action.json");
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }

        Action getActionFromJson() {

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
        {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0},         
        {Action::UPGRADE, nullptr, 0, 0, 0, 2, 7, 42},          
        {Action::ABILITYUSE, nullptr, 0, 0, 0, 0, 10, 42}       
    };

    Action action = {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0};

    Strategy strategy = {"6-9", 420, 650, 63, actions};

    Strategy strategyV2 = {"6-10", 32, 42, 422, actions}; 

    Generation generation6 = {6, "5-5", 5000, "6-9", 420, {strategy, strategyV2}};

    generationHandler manHandler;
    manHandler.setGenFilePath(6); // for generation 6

    //manHandler.writeGenerationToJson(generation6);

    //manHandler.writeActionToJson(action);
    return 0;
}