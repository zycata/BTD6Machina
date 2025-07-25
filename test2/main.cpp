#include<iostream>


#include "my_class.cpp" // DONRT DO THIS (but it works)

// g++ my_class.cpp main.cpp -o main.exe 
using namespace std;
int main() {
    myObject obj(69);
    obj.soyAdmen();
}