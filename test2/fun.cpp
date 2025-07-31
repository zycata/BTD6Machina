
#include <iostream>
#include <windows.h>

void listFilesInFolder(const std::string& folderPath) {
    std::string searchPath = folderPath + "\\*";
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Cannot open directory " << folderPath << std::endl;
        return;
    }

    do {
        std::string name = findData.cFileName;
        if (name != "." && name != "..") {
            std::cout << name << std::endl;
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
}

int main() {
    listFilesInFolder("bruteforcefile"); // Change "folder" to your target directory
    return 0;
}
