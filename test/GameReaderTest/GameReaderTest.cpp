#include "../../src/jsonHandlers/GameReader.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;
// 
// in this folder ofc bevause im the goat
// compile using g++ test/GameReaderTest/GameReaderTest.cpp src/jsonHandlers/GameReader.cpp -o test/GameReaderTest/GameReaderTest.exe


template<typename T>
bool assertEquals(const T& expected, const T& actual, const string& message) {
    if (expected != actual) {
        cerr << "Assertion failed: " << message << " Expected: " << expected << ", Actual: " << actual << endl;
        return false;
    } else {
        cout << "Test passed: " << message << endl;
    }
    return true;
}

void testReaderValues() {
    
}

int main() {
    GameReader reader("testJsons/test1.json");
    reader.initialize();

    
    reader.testMetrics();
        
    reader.changeFilePath("testJsons/test2.json");

    reader.testMetrics();

    return 0;
}
