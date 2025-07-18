#include <iostream>

#include <windows.h>
#include <cctype>
#include "mouseControl.h"
#include <map>
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
    {25, 0x19} // DESPERADO NOT SET PLEASE CHANGE jk i did change it it's P allegedly...
};

void addTowers(){
    towerLocations[0][0] = heroLocation[0];
    towerLocations[0][1] = heroLocation[1]; 
    int side = 1; // 1 for right, -1 for left
    int verticalOffset;
    for (int i = 1; i < page1Towers; i++) {
        if (i % 2 == 0) {
            side = -1; // left
            verticalOffset = cardHeight;
        } else {
            side = 1; // right
            verticalOffset = 0;
        }
        towerLocations[i][0] = towerLocations[i-1][0] + side*cardWidth ;
        towerLocations[i][1] = towerLocations[i-1][1] + verticalOffset ;
    }
    towerLocations[page1Towers][0] = heroLocation[0];
    towerLocations[page1Towers][1] = heroLocation[1]; 
    for (int i = page1Towers + 1; i < totalTowers; i++) {
        if (i % 2 == 0) {
            side = -1; // left
            verticalOffset = cardHeight;
        } else {
            side = 1; // right
            verticalOffset = 0;
        }
        towerLocations[i][0] = towerLocations[i-1][0] + side*cardWidth ;
        towerLocations[i][1] = towerLocations[i-1][1] + verticalOffset ;
    }
}

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

void scrollMouse(int direction) {
    // direction = 1 for up, -1 for down
    CONST int x = heroLocation[0];
    CONST int y = heroLocation[1];
    CONST int amount = 16 * direction; // 16 is the scroll amount per tick
    moveMouse(x, y);
    Sleep(300);
    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = amount;  // 120 units = 1 scroll "tick"
    for (int i = 0; i < abs(amount); ++i) {
        SendInput(1, &input, sizeof(INPUT));
    }
    //SendInput(1, &input, sizeof(INPUT));
}

void pagedown() {
    scrollMouse(-1);
    pageState = 1;
}

void pageup() {
    scrollMouse(1);
    pageState = 0;
}

void testListMake() {
    for (int i = 0; i < totalTowers; ++i) {
        cout << "Row " << i << ": ";
        for (int j = 0; j < 2; ++j) {
            cout << towerLocations[i][j] << " ";
        }
        cout << endl;
    }
}

bool placeTowerOld(int tower, int x, int y) {
        

        if (tower >= page1Towers) {
            if (pageState == 0) {
                pagedown();
            }
        } else {
            if (pageState == 1) {
                pageup();
            }
        }
        CONST int delay = 50;
        Sleep(delay*10);
        int towerX = towerLocations[tower][0];
        int towerY = towerLocations[tower][1];
        moveMouse(towerX, towerY);
        Sleep(delay);
        clickMouse();
        Sleep(delay);
        moveMouse(x, y);
        Sleep(delay);
        unclickMouse();
        Sleep(delay);
        moveMouse(heroLocation[0], heroLocation[1]);
        Sleep(delay*3);
        return true;
    }
// add something to check if the pixels given are valid
// return false when pixels are not valid

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

    bool placeTower(int tower, int x, int y) {
        // hero key scan doesnt work because fuckass game :sob: 
        if (tower == 0) {
            placeHero(x,y);
            return true;
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
        findWindow();
        addTowers();
        return true;
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

    addTowers(); 
    findWindow();
    
    
    placeHero( 100, 200);
    placeTower(17, 300, 400); 
    placeTower(13, 300, 690);
    upgradeTower(300, 690, 2);
    upgradeTower(300, 690, 2);
    upgradeTower(300, 690, 1);
    upgradeTower(300, 690, 1);
    upgradeTower(300, 690, 1);
    upgradeTower(300, 690, 1); 
    upgradeTower(300, 690, 1); 


    moveMouse(0, 0);
    return 0;
} */