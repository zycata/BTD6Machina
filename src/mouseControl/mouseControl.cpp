#include <iostream>
#include <windows.h>
#include <cctype>
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

short charToVirtualKey(char c) {
    SHORT vk = VkKeyScanA(c);
    return vk;
}

void pressKey(char c) {
    INPUT input[2] = {};
    short vk_combo = charToVirtualKey(c);

    if (vk_combo == -1) return; // character not supported

    // Extract virtual key and shift state
    BYTE vk = LOBYTE(vk_combo);
    BYTE shiftState = HIBYTE(vk_combo);

    int inputIndex = 0;

    // If shift is needed
    if (shiftState & 1) {
        input[inputIndex].type = INPUT_KEYBOARD;
        input[inputIndex].ki.wVk = VK_SHIFT;
        inputIndex++;
    }

    // Press key
    input[inputIndex].type = INPUT_KEYBOARD;
    input[inputIndex].ki.wVk = vk;
    inputIndex++;

    // Release key
    input[inputIndex].type = INPUT_KEYBOARD;
    input[inputIndex].ki.wVk = vk;
    input[inputIndex].ki.dwFlags = KEYEVENTF_KEYUP;
    inputIndex++;

    // If shift was pressed, release it
    if (shiftState & 1) {
        input[inputIndex].type = INPUT_KEYBOARD;
        input[inputIndex].ki.wVk = VK_SHIFT;
        input[inputIndex].ki.dwFlags = KEYEVENTF_KEYUP;
        inputIndex++;
    }

    SendInput(inputIndex, input, sizeof(INPUT));
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



// add something to check if the pixels given are valid
// return false when pixels are not valid
bool placeTower(int tower, int x, int y) {
    

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


void testListMake() {
    for (int i = 0; i < totalTowers; ++i) {
        cout << "Row " << i << ": ";
        for (int j = 0; j < 2; ++j) {
            cout << towerLocations[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    cout << "Script Started" << endl;

    addTowers(); 
    findWindow();
    /*
    testListMake(); 
    
    
    placeTower(21, 100, 200);
    placeTower(22, 300, 400); 
    placeTower(2, 300, 690);
    upgradeTower(300, 690, 2);
    upgradeTower(300, 690, 2);
    upgradeTower(300, 690, 1);
    upgradeTower(300, 690, 1);
    upgradeTower(300, 690, 1);
    upgradeTower(300, 690, 1); 
    upgradeTower(300, 690, 1); */

    moveMouse(0, 0);
    cout << "Towers placed: " << endl;
    return 0;
}