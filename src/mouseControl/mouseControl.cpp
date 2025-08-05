#include <iostream>

#include <windows.h>
#include <cctype>
#include "mouseControl.h"
#include <map>
#include <stdexcept>
using namespace std;

struct towerLocation {
    int x;
    int y;
};



int pageState = 0; // 0 for page 1, 1 for page 2
CONST int cardHeight = 90;
CONST int cardWidth = 72;
CONST int totalTowers = 23;
CONST int page1Towers = 12;
CONST int heroLocation[2] = { 1145, 175 }; // Hero location, RELATIVE TO THE WINDOW (as of rn for 720x1280)
int windowX = 0;
int windowY = 0;

int towerLocations[totalTowers][2] = {};
map<int, BYTE> towerKeyScan = {
    {0, 0x16},  // Hero        → U
    {1, 0x10},  // Dart        → Q
    {2, 0x11},  // Boomerang   → W
    {3, 0x12},  // Bomb        → E
    {4, 0x13},  // Tack        → R
    {5, 0x14},  // Ice         → T
    {6, 0x15},  // Glue        → Y
    {7, 0x2C},  // Sniper      → Z
    {8, 0x2D},  // Sub         → X
    {9, 0x2E},  // Buccaneer   → C
    {10, 0x2F}, // Ace         → V
    {11, 0x30}, // Heli        → B
    {12, 0x31}, // Mortar      → N
    {13, 0x32}, // Dartling    → M
    {14, 0x1E}, // Wizard      → A
    {15, 0x1F}, // Super       → S
    {16, 0x20}, // Ninja       → D
    {17, 0x21}, // Alch        → F
    {18, 0x22}, // Druid       → G
    {19, 0x18}, // Mermonkey?  → O
    {20, 0x23}, // Farm        → H
    {21, 0x24}, // Spactory    → J
    {22, 0x25}, // Village     → K
    {23, 0x26}, // Engineer    → L
    {24, 0x17},  // Beast       → I
    {25, 0x19} // DESPERADO NOT SET PLEASE CHANGE jk i did change it it's P allegedly... P diddy haha im so funny
};

std::map<int, BYTE> numberScanCodes = {
    {1, 0x02}, // '1'
    {2, 0x03}, // '2'
    {3, 0x04}, // '3'
    {4, 0x05}, // '4'
    {5, 0x06}, // '5'
    {6, 0x07}, // '6'
    {7, 0x08}, // '7'
    {8, 0x09}, // '8'
    {9, 0x0A}, // '9'
    {0, 0x0B}  // '0'
};

void moveMouse(int x, int y) {
    // Set the cursor position
    SetCursorPos(x + windowX, y + windowY);
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




void placeHero( int x, int y) {
        
        CONST int delay = 50;
        moveMouse(1075, 107); // Intiailize the window
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
        Sleep(delay);

        Sleep(delay);
        moveMouse(heroLocation[0], heroLocation[1]);
        Sleep(delay);
        clickMouse();
        Sleep(delay);
       
        moveMouse(x, y);
        Sleep(delay);

        Sleep(delay);
        unclickMouse();
       
}


namespace mouseControl {

    void clickOnTower(int x, int y) {
        CONST int delay = 80;
        moveMouse(x, y);
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
        Sleep(delay);
    }

    void initializeWindow() {
        CONST int delay = 50;
        moveMouse(1075, 107); // Intiailize the window
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
        Sleep(delay);
    }
    // only works with abilities 0 - 9, nothing more
    void useAbility(int abilityIndex) {
        pressKeyScan(numberScanCodes[abilityIndex]);
        
    }

    bool placeTower(int tower, int x, int y) {
        // hero key scan doesnt work because fuckass game :sob: 
        if (tower == 0) {
            placeHero(x,y);
            return true;
        }

        if (tower >= towerKeyScan.size()) {
            throw std::runtime_error("Invalid tower code (probably too big)");
        }

        CONST int delay = 50;
        moveMouse(1075, 107); // Intiailize the window
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
        Sleep(delay);
        
        moveMouse(x, y);
        Sleep(delay);
        pressKeyScan(towerKeyScan[tower]);
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
       
        return true;
    }

    void upgradeTower(int x, int y, int path) {
        int delay = 50;
        moveMouse(x, y);
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
        Sleep(delay);
        
        switch (path) {
            case 0:
                pressKeyScan(0x33); // 0x31 = scan code for ','
                break;
            case 1:
                pressKeyScan(0x34); // 0x34 = scan code for '.'
                break;
            case 2:
                pressKeyScan(0x35); // 0x35 = scan code for '/'
                break;
            default:
                cout << "Invalid path" << endl;
                return;
        }


        
        Sleep(delay);
        moveMouse(x, y);
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        unclickMouse();
        Sleep(delay);
    }

    bool findWindow() {
        const wchar_t* windowTitle = L"BloonsTD6"; // Replace with the actual title (case sensitive)

        HWND hwnd = FindWindowW(NULL, windowTitle);

        if (hwnd == NULL) {
            cerr << "Window not found!" << endl;
            return false;
        } else {
            cout << "Window found!" << endl;
        }
        RECT rect;
        GetWindowRect(hwnd, &rect);
        windowX = rect.left;
        windowY = rect.top;
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        cout << "Window Position: (" << windowX << ", " << windowY << ")" << endl;
        cout << "Window size: " << width << " x " << height << endl;



        return true;


    }

    bool initializeMouseControls() {
        return findWindow();
        
    }

    void ClickStartNextRound() {
        moveMouse(1222, 705);
        Sleep(50);
        clickMouse();
        Sleep(50);
        unclickMouse();
    }

    void restartGameWhenOver(bool roundinitialandchimps) {
        if (roundinitialandchimps == true) {
            moveMouse(647, 569);
        } else {
            moveMouse(575, 570);
        }
        Sleep(50);

        clickMouse();
        Sleep(50);
        unclickMouse();
        Sleep(50);
        moveMouse(757, 515);
        Sleep(200);
        clickMouse();
        Sleep(50);
        unclickMouse();
        
    }
}





/*
using namespace mouseControl;
int main() {
    cout << "Script Started" << endl;
    Sleep(1000 );
    useAbility(1);
    return 0;
} */