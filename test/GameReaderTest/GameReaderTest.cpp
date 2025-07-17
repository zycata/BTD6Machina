#include "GameReader.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
// 
// in this folder ofc bevause im the goat
// compile using g++ GameReaderTest.cpp GameReader.cpp -o GameReaderTest.exe
int main() {
    GameReader reader("testJsons/test1.json");
    reader.initialize();

    
    reader.testMetrics();
        
    reader.changeFilePath("testJsons/test2.json");

    reader.testMetrics();

    return 0;
}
