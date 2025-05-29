#include <iostream>
#include <windows.h>
#include <vector>
#include <cctype>
#include <map>
using namespace std;




void moveMouse(int x, int y) {
    // Set the cursor position
    SetCursorPos(x , y );
}

void clickMouse() {
    // Simulate a mouse click
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    
}

void unclickMouse() {
    // Simulate a mouse click
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void pressKeyScan(BYTE scanCode) {
    INPUT input[2] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wScan = scanCode;
    input[0].ki.dwFlags = KEYEVENTF_SCANCODE;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wScan = scanCode;
    input[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void scrollMouse(int amount) {
    // Scroll the mouse wheel
    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = amount;  // 120 units = 1 scroll "tick"
    SendInput(1, &input, sizeof(INPUT));
}


map<int, string> alphabetMap = {
    {0, "A"},
    {1, "B"},
    {2, "C"},
    {3, "D"},
    {4, "E"},
    {5, "F"}
};

map<int, BYTE> alphabetScan = {
    {0, 0x1E}, // A
    {1, 0x30}, // B
    {2, 0x2E}, // C
    {3, 0x20}, // D
    {4, 0x12}, // E
    {5, 0x21}  // F
};
int scrollticks = 35;
int xLocation = 324; // Placeholder for x location
int boxLocations[4] = {787, 837, 888, 920}; // Placeholder for box locations in y coords
int submitx = 472; // Placeholder for submit button x location
int submity = 1104; // Placeholder for submit button y location
int delay = 100; // Delay in milliseconds
void clicks(vector<int> possibility) {
    

    // Type the letters corresponding to the digits in the possibility vector
    for (int i = 0; i < 4; ++i) {
        int digit = possibility[i];
        moveMouse(xLocation, boxLocations[i]); // Move to the specific box location
        clickMouse(); // Click to focus the box
        unclickMouse(); // Release the click
        Sleep(delay);
        pressKeyScan(0xE); // Press the corresponding key
        pressKeyScan(alphabetScan[digit]);
        Sleep(delay); // Wait between key presses
    }

    // Press Enter to submit the input
    moveMouse(submitx, submity);
    clickMouse();
    unclickMouse();
    Sleep(delay * 15); // Wait for the submission to register
    scrollMouse(scrollticks * -120); // Scroll down to the next box
    Sleep(delay * 10); // Wait for the scroll to register
}

// generates all plausible outcomes for digits 0 - 5, each being a vector of 4 integers, with no duplicates in each
int digits = 6;
void generatePlausibleOutcomes() {
    for (int i = 0; i < digits; ++i) {
        for (int j = 0; j < digits; ++j) {
            if (j == i) continue;
            for (int k = 0; k < digits; ++k) {
                if (k == i || k == j) continue;
                for (int l = 0; l < digits; ++l) {
                    if (l == i || l == j || l == k) continue;

                    vector<int> outcome = {i, j, k, l};
                    cout << "Trying outcome: ";
                    for (int digit : outcome) {
                        cout << alphabetMap[digit] << " ";
                    }
                    clicks(outcome); // Call the clicks function with the current outcome
                    // Process the outcome (e.g., print it)

                    
                    cout << endl;
                }
            }
        }
    }
}

// link libraries with g++ -static -o test2/bruteforce.exe test2/bruteforce.cpp

int main() {
    cout << "Standard Delay Time: " << delay << "ms" << endl;
    cout << "Starting the automation..." << endl;
    cout << "Enter the x location for the boxes: ";
    cin >> xLocation;
    cout << "Enter the y locations for the boxes (4 values separated by spaces): ";
    for (int i = 0; i < 4; ++i) {
        cin >> boxLocations[i];
    }
    cout << "Enter the x and y locations for the submit button: ";
    cin >> submitx >> submity;
    cout << "Locations set. Ready to generate outcomes." << endl;
    system("pause"); // Wait for user to set up the locations
    cout << "Starting to generate outcomes..." << endl;

    cout << "Generating plausible outcomes for digits 0-5..." << endl;
    //generatePlausibleOutcomes();
    generatePlausibleOutcomes(); // Call the function to generate outcomes
    Sleep(1000); // Wait for a second before finishing

    cout << "Done generating outcomes." << endl;
    return 0;
}