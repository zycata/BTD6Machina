#pragma once
#ifndef JSONMANAGER_HPP
#define JSONMANAGER_HPP





#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include "json.hpp"
#include "../gameTypes.h"


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

struct AlgorithmSettings {
    std::string filePathToGameData;
    Difficulty difficulty;
    std::vector<int> towersAllowed;

    int roundsCutOffPerGeneration;
    int childrenPerGeneration;

};

// wow function overloading for a third time??? This is certainly a code of all time
inline std::string to_string(Difficulty type) {
    switch (type) {
        case EASY: return "EASY";
        case MEDIUM: return "MEDIUM";
        case HARD: return "HARD";
        case IMPOPPABLE: return "IMPOPPABLE";
        case CHIMPS: return "CHIMPS";
        default: return "UNKNOWN";
    }
}


inline std::string to_string(Action::ActionType type) {
    switch (type) {
        case Action::PLACE: return "PLACE";
        case Action::UPGRADE: return "UPGRADE";
        case Action::ABILITYUSE: return "ABILITYUSE";
        default: return "UNKNOWN";
    }
}



inline void to_json(json& j, const Action& action) {
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
// why the fuick was there an error here and it just disappeared intellisenbse PLEAS lockk in 2025/07/27 <- adding dates to these messages because Im really funny
inline void to_json(json& j, const Strategy& strategy) {
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
inline void to_json(json& j, const Generation& generation) {
    json children = generation.children;
    j["generationNumber"] = generation.generationNumber;
    j["parentID"] = generation.parentID;
    j["parentScore"] = generation.parentScore;
    j["bestChildId"] = generation.bestChildId;
    j["bestChildScore"] = generation.bestChildScore; // mfw when i forget to add this  
    j["children"] = children;
    // mewhen children...
}


// gonna use function overloading for another function?? TS cannort be real
inline void from_json(const json& j, Action& action) {
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

inline Difficulty difficulty_to_enum(std::string& difficulty_str) {
    //std::string difficulty_str = j.get<std::string>();
    if (difficulty_str == "EASY") return Difficulty::EASY;
    else if (difficulty_str == "MEDIUM") return Difficulty::MEDIUM;
    else if (difficulty_str == "HARD") return Difficulty::HARD;
    else if (difficulty_str == "IMPOPPABLE") return Difficulty::IMPOPPABLE;
    else if (difficulty_str == "CHIMPS") return  Difficulty::CHIMPS;
    else throw std::runtime_error("Invalid difficulty: " + difficulty_str);
}

inline void from_json(const json& j, Strategy& strategy) {
    j.at("ID").get_to(strategy.ID);
    
    std::string difficulty_str = j.at("difficulty").get<std::string>();
    strategy.difficulty = difficulty_to_enum(difficulty_str);
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
inline void from_json(const json& j, Generation& generation) {
    j.at("generationNumber").get_to(generation.generationNumber);
    j.at("parentID").get_to(generation.parentID);
    j.at("parentScore").get_to(generation.parentScore);
    j.at("bestChildScore").get_to(generation.bestChildScore);
    j.at("bestChildId").get_to(generation.bestChildId);
    j.at("children").get_to(generation.children);
}
// fuck this function overloading shit is kinda genius, i think im might just make this single class do all the json stuff, including getting stuff from the gameDATA
// FUCKK NOOO MORE WORK
// guys compilation tiome is O(1) since I only ever compile one projewct
// I can see why people say building projects is how you learn --> hola soy admen

inline void from_json(const json& j, AlgorithmSettings& settings) {
    j.at("filePathToGameData").get_to(settings.filePathToGameData);
    std::string type_str = j.at("difficulty").get<std::string>();
    settings.difficulty = difficulty_to_enum(type_str);
    j.at("towersAllowed").get_to(settings.towersAllowed);

    j.at("roundsCutOffPerGeneration").get_to(settings.roundsCutOffPerGeneration);
    j.at("childrenPerGeneration").get_to(settings.childrenPerGeneration);

}


// TODO: add a function to retrive the best child from a generation struct --> tommorow trust me bro
class JsonManager {
    
    private:
        const int soyamdendoija = 0; // shitpost

        std::string generationFilePath;

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
        JsonManager() : generationFilePath("generations/generation.json") {} // Default constructor sets a default file path

        JsonManager(std::string filePath) : generationFilePath(filePath) {} // Constructor that allows setting a custom file path

        void setGenFilePath(int generationNumber) {
            std::string generationNumberString = std::to_string(generationNumber);
            generationFilePath = "generations/generation_" + generationNumberString + ".json";
            
        }
        
        std::string getGenFilePath() {
            return generationFilePath;
        }

        

        // wait you can name these whatever thje fuick you want HELLL YEAH, IM NAMING THE NEXT ONE AFTER MY DAD THJAT LEFT ME
        // unfortunately due to the fact thjat we live in a society, I cannot name it after my dad that left me, so I will name it after my mom that left me
        // just kidding cant do that either gotta have some fuckass practical name
        // oh yeah might as well document this function, pretty much just returns an object of the type you want from the json file, technically it's only needed for generation struct, but other types for testing purposes

        template<typename StrategyActionOrGeneration>
        StrategyActionOrGeneration getFromJson(std::string filePath = "") {
            if (filePath.empty()) {
                filePath = generationFilePath;  
            }
            return readActionFromJson(filePath).template get<StrategyActionOrGeneration>();
        }

        Generation getGenerationFromJson(std::string filePath = "") {
            if (filePath.empty()) {
                filePath = generationFilePath;  
            }
            return readActionFromJson(filePath).template get<Generation>();
        }

        AlgorithmSettings getAlgorithmSettingsFromJson(const std::string& filePath = "config/settings.json") {
            json j = readActionFromJson(filePath);
            if (j.is_null()) {
                throw std::runtime_error("Failed to read algorithm settings from JSON file: " + filePath);
            }
            return j.get<AlgorithmSettings>();
        }

        
        std::vector<int> loadTowerCostsFromJson(const std::string& filePath = "config/tower_costs.json") {
            json jsonOpt = readActionFromJson(filePath);
            if (jsonOpt.is_null()) {
                throw std::runtime_error("Failed to read tower costs from JSON file: " + filePath);
            }
            int TOTALTOWERCOUNT = 26;
            std::vector<int> towerCosts(TOTALTOWERCOUNT, INVALID); // omg you have to preallocate "26" spots before assigning by index because by default it's no spots
            // mfw when im doing a project that could be done in python but choose c++ because I love accessing invalid ram 
            // exit  code=3221225477 is just accessing invalid ram (Me when i want to access the wrong electrons.... pretty please windows???)
            for (size_t i = 0; i < TOTALTOWERCOUNT; ++i) {
                try {
                    //std::cout << "Loading tower cost for: " << kTowerNames[i] << std::endl;
                    //std::cout << "Tower cost: " << jsonOpt.at(kTowerNames[i]).get<int>() << std::endl;
                    towerCosts[i] = jsonOpt.at(kTowerNames[i]).get<int>();
                } catch (const nlohmann::json::out_of_range& e) {
                    std::cerr << "Error: Tower cost for " << kTowerNames[i] << " not found in JSON file." << std::endl;
                    towerCosts[i] = INVALID; // Set to INVALID if not found
                }
                
            }
            return towerCosts; // if i had a nickel for everytime I fucked something up cause i forgot a return, id have two nickles which means im a dumbass
        }

        std::vector<std::vector<std::vector<int>>> loadTowerUpgradesFromJson(const std::string& filePath = "config/tower_upgrades.json") {
            json j = readActionFromJson(filePath);
            
            if (j.is_null()) {
                throw std::runtime_error("Failed to read or parse tower upgrades JSON.");
            }

            const int TOWERS = 26, PATHS = 3, TIERS = 5;
            std::vector<std::vector<std::vector<int>>> upgrades(TOWERS, std::vector<std::vector<int>>(PATHS, std::vector<int>(TIERS)));

            for (int t = 0; t < TOWERS; ++t)
                for (int p = 0; p < PATHS; ++p)
                    for (int u = 0; u < TIERS; ++u) // tpu tensor processing unit moment (im so funny pls laugh)
                        upgrades[t][p][u] = j[t][p][u];
            if (upgrades.size() != TOWERS || upgrades[0].size() != PATHS || upgrades[0][0].size() != TIERS) {
                throw std::runtime_error("Invalid tower upgrades JSON structure.");
            }
            return upgrades;
        }

        


        // wait template typename t is a lifehack i lied c++ is the goat i love c++ 
        // like did this shit earlier but using for this is actually an eyeopener
        // hey everybody me from a week later this language is ass

        template<typename T>
        void writeToJson(const T& generation, std::string filePath = "") {
            if (filePath.empty()) {
                filePath = generationFilePath;  
            }
            json j_array = generation;
            std::ofstream out_file(filePath);
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }

        void writeGenerationToFile(const Generation &generation,  std::string genInfoFilePath = "") {

            if (genInfoFilePath.empty()) {
                genInfoFilePath = "generations/currentGenInformation.json";
            }
            writeToJson(generation);
            int currentGenerationNumber = generation.generationNumber;
            json j_array;
            j_array["generationNumber"] = currentGenerationNumber;
            std::ofstream out_file(genInfoFilePath);
            if (out_file.is_open()) {
                out_file << j_array.dump(2); // Pretty print with 2-space indentation
                out_file.close();
            } else {
                std::cerr << "Error: Could not open file for writing!" << std::endl;
                
            }
        }

        int getCurrentGenerationNumber(std::string genInfoFilePath = "generations/currentGenInformation.json") {
            json j = readActionFromJson(genInfoFilePath);
            if (j == nullptr) {
                std::cerr << "No previously made generations, making something completely new.. This filePath is empty -> " << genInfoFilePath << std::endl;
                return 0;
            }
            else if (j.is_null()) {
                std::cerr << "Error: Could not read current generation information from " << genInfoFilePath << std::endl;
                return -1; // Indicate failure to read
            }
            return j.at("generationNumber").get<int>();
        }

        Strategy *getStartingStrategy() {
            json j = readActionFromJson("generations/FirstStrategy.json");
            if (j == nullptr) {
                return nullptr;
            } 
            Strategy s = j.get<Strategy>();
            return new Strategy(s);
        }
};


// pankake i swear to god you actuall infected me with the gotta "try to" optimize everything disesase
// like ik ts is not optimized but GODDAMNIT the urge to make tiny ass improvements with negligible results is actually killing me
// how about I actually get a working build before doing that
// c++ pointers are cool, but you know what's cooler? 
// having oop not shoved straight up ur ass so hard that you start vomiting it out

#endif