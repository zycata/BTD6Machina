#include<iostream>

#include<filesystem>
#include<string>
using namespace std;

void soyadmen() {
    cout << "hey" << endl;
}
int main() {
    //Finalizer logOnExit{[] { soyadmen(); }}; 
    string folderDirectory = "testincludingotherfiles";

     if (!std::filesystem::exists(folderDirectory) || !std::filesystem::is_directory(folderDirectory)) {
        std::cerr << "Error: Directory does not exist or is not a directory." << std::endl;
        return 1;
    }
    for (const auto &file : filesystem::directory_iterator(folderDirectory)) {
        
    }
    return 0;
}