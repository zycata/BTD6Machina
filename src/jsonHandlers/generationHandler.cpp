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

    Difficulty difficulty;
    //enum difficulty { EASY, MEDIUM, HARD } difficulty;
    
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

// wow function overloading for a third time??? This is certainly a code of all time
std::string to_string(Difficulty type) {
    switch (type) {
        case EASY: return "EASY";
        case MEDIUM: return "MEDIUM";
        case HARD: return "HARD";
        case IMPOPPABLE: return "IMPOPPABLE";
        case CHIMPS: return "CHIMPS";
        default: return "UNKNOWN";
    }
}


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
        {"difficulty", to_string(strategy.difficulty)}, 
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
    action.tower = nullptr;
    j.at("path").get_to(action.path);
    j.at("round").get_to(action.round);
    j.at("towerId").get_to(action.towerId);

}

void from_json(const json& j, Strategy& strategy) {
    j.at("ID").get_to(strategy.ID);
    
    std::string difficulty_str = j.at("difficulty").get<std::string>();
    if (difficulty_str == "EASY") strategy.difficulty = EASY;
    else if (difficulty_str == "MEDIUM") strategy.difficulty = MEDIUM;
    else if (difficulty_str == "HARD") strategy.difficulty = HARD;
    else if (difficulty_str == "IMPOPPABLE") strategy.difficulty = IMPOPPABLE;
    else if (difficulty_str == "CHIMPS") strategy.difficulty = CHIMPS;
    else throw std::runtime_error("Invalid difficulty: " + difficulty_str);
    //j.at("difficulty").get_to(strategy.difficulty); // difficulty
    j.at("endCash").get_to(strategy.endCash);
    j.at("roundObtained").get_to(strategy.roundObtained);
    j.at("score").get_to(strategy.score);
    j.at("actions").get_to(strategy.actions);
}

/* life lore drop: i was playing minecraft with a friend and he was like yo can my gf join so his gf joined us on the call, but then we did the matching pfps of the ceo astronomer cheating with his wife
    and then she said "i feel like im third wheeling you two here despite being the girlfriend",
    GITHUB COPILOT STOP RECOMMENDING STORY SUGGESTIONS RECOMMEND ME CODE
*/
void from_json(const json& j, Generation& generation) {
    j.at("generationNumber").get_to(generation.generationNumber);
    j.at("parentID").get_to(generation.parentID);
    j.at("ParentScore").get_to(generation.parentScore);
    j.at("bestChildId").get_to(generation.bestChildId);
    j.at("children").get_to(generation.children);
}
// fuck this function overloading shit is kinda genius, i think im might just make this single class do all the json stuff, including getting stuff from the gameDATA
// FUCKK NOOO MORE WORK
// guys compilation tiome is O(1) since I only ever compile one projewct
// I can see why people say building projects is how you learn --> hola soy admen




class generationHandler {
    
    private:
        const int soyamdendoija = 0; // shitpost

        std::string filePath;
        json readActionFromJson(std::string filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open JSON file at " << filePath << std::endl;
                // Sleep(50); 
                return nullptr; // Indicate failure to open
            }
            file.seekg(0, std::ios::end);
            if (file.tellg() == 0) {
                std::cerr << "Warning: JSON file is empty at " << filePath << ". Retrying..." << std::endl;
                file.close();
                return nullptr; // Indicate an empty file, so updateValues can retry
            }
            file.seekg(0, std::ios::beg); // Reset file pointer to the beginning for parsing

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
            filePath = "jsonTests/generation_" + generationNumberString + ".json";
            
        }

        void writeActionToJson(const Action& action) {
            json j_array = action;
            std::ofstream out_file("jsonTests/action.json");
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }

        json getActionFromJson() {
            return readActionFromJson("jsonTests/action.json");
        }

        json getStrategyFromJson() {
            return readActionFromJson("jsonTests/strategy.json");
        }

        void writeStrategyToJson(const Strategy& strategy) {
            json j_array = strategy;
            std::ofstream out_file("jsonTests/strategy.json");
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


using namespace std;
int main() {
    
    std::vector<Action> actions = {
        {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0},         
        {Action::UPGRADE, nullptr, 0, 0, 0, 2, 7, 42},          
        {Action::ABILITYUSE, nullptr, 0, 0, 0, 0, 10, 42}       
    };

    Action action = {Action::PLACE, nullptr, 10, 20, 1, -1, 5, 0};

    Strategy strategy = {"6-9", HARD, 420, 650, 63, actions};

    Strategy strategyV2 = {"6-10", HARD, 32, 42, 422, actions}; 

    Generation generation6 = {6, "5-5", 5000, "6-9", 420, {strategy, strategyV2}};

    generationHandler manHandler;
    manHandler.setGenFilePath(6); // for generation 6
    json j = manHandler.getActionFromJson();

    Action testAction = j.get<Action>();

    cout << testAction.towerType <<  endl;
    cout << to_string(testAction.type) <<  endl;

    manHandler.writeStrategyToJson(strategy);
    json jj = manHandler.getStrategyFromJson();

    Strategy theStrat = jj.get<Strategy>();

    // fun fact semicolon based languages use either the semicolon or curly braces to determine wether a statement ends, which means that tabs and new lines are option, so in ortder to not be
    // replaced by AI, just write ur entire code in a single line and fuck it up (ai can probably parse it but idk it prolly ass)
    // idk purely a fun fact dont actually do this unless ur making ur own shit go ahead (probably still better than pirate software code)
    // LOOK I KNOW I USE MAGIC NUMBERS BUT THEY"RE ALWAYS TEMPORARY PLACEHOLDERS
    cout << "End Cash: " << theStrat.endCash << " RoundObtained: " << theStrat.roundObtained << endl; cout << "Actions Size: " << theStrat.actions.size() << endl;

    //manHandler.writeGenerationToJson(generation6);
    
    //manHandler.writeActionToJson(action);
    return 0;
}