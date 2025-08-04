#include "../../src/jsonHandlers/GameReader.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <thread>
#include <vector>
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
    GameReader reader("testJsons/test1.json");
    assertEquals(0, static_cast<int>(reader.getAbilities().size()), "First Ability offColdown");
    assertEquals(false, reader.didGameOver(), "Game is not over here");

    assertEquals(false, reader.didGameWon(), "Game has not been won yet...");
    assertEquals(650, reader.getCash(), "Cash should be at 650");
    reader.changeFilePath("testJsons/test2.json");
    assertEquals(9954834, reader.getCash(), "Cash should be at 9954834");
    assertEquals(3, static_cast<int>(reader.getAbilities().size()), "Ability should have 3 of em now");
    
    



}

void func() {
    Sleep(2000);
    system("pause");
}



void testEmptyStr() {
    GameReader reader("testJsons/Invalid.json");
    reader.didGameOver();
    cout << "Test Passed: is able to not immediately fail an empty json" << endl;
    // if thing faikls here then test doesnt pass (infinite iq testing strat)
    // actually such a bad way to do this, but like i mean... how else??
    // also probably will add something to click exp when level ups happen or something

}

void testGettingAbilities() {
    GameReader reader("testJsons/test2.json");
    cout << "here works" << endl;
    reader.getCash();
    vector<int> s = reader.getAbilities();
    for (const auto &h : s) {
        cout << h << endl;
    }
}
int main() {
    testReaderValues();
    //testEmptyStr();
    testGettingAbilities();
    system("pause");
    return 0;
}
