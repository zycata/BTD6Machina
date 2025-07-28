#include "../../src/jsonHandlers/GameReader.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <thread>
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
    assertEquals(false, reader.didGameOver(), "Game is not over here");
    assertEquals(false, reader.didGameWon(), "Game has not been won yet...");
    assertEquals(650, reader.getCash(), "Cash should be at 650");
    reader.changeFilePath("testJsons/test2.json");
    assertEquals(1234, reader.getCash(), "Cash should be at 1234");



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


int main() {
    testReaderValues();
    testEmptyStr();
    system("pause");
    return 0;
}
