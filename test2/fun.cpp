#include<iostream>
#include"../src/gameTypes.hpp"
using namespace std;

void soyadmen() {
    cout << "hey" << endl;
}
int main() {
    //Finalizer logOnExit{[] { soyadmen(); }}; 
    int byteSize = sizeof(Action);
    cout << "size of Action struct: " << byteSize << endl;
    return 0;
}