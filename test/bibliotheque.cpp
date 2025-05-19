#include <iostream>
#include <cmath>
#include "bibliotheque.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
namespace bibliotheque {
    int yap() {
        std::cout << "Hello from bibliotheque" << std::endl;
        return 5;
    }

    void test() {
        std::cout << "Test function in bibliotheque" << std::endl;
    }

}


using namespace std;
using namespace bibliotheque;

int roundToNearestFive(float value) {
    return static_cast<int>(5 * round(value / 5.0f));
}

int roundToNearest5(int num, float multiplier) {
    float value = num * multiplier;
    return static_cast<int>(5 * round(value / 5.0f));
}




int main() {
    
    srand(time(0));
    vector<int> randomints;
    map<int, int> randintmap;
// Generate a random number between 0 and 9
    for (int i = 0; i < 1000; ++i) {
        int randomNum = rand() % 2;
        randomints.push_back(randomNum);
    }
    
    for (int i : randomints) {
        if (randintmap.find(i) == randintmap.end()) {
            randintmap[i] = i;
        } else {
            randintmap[i]++;
        }
    }
    for (auto& pair : randintmap) {
        cout << "Number: " << pair.first << ", Percentage occured: " << (pair.second*100) / randomints.size() << "%" << endl;
    }
    return 0;

}  