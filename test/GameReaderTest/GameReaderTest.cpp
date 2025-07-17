#include "GameReader.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
// compile using g++ GameReaderTest.cpp GameReader.cpp -o GameReaderTest.exe
int main() {
    GameReader reader("C:/Users/yanxi/Documents/Btd6Machine/Cpppractice/src/gameInfo/gameData.json");
    reader.initialize();

    while (true){
        reader.testMetrics();
        
    }

    cout << "Game Over!" << endl;
    return 0;
}
