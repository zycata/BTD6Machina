
// my_lib.cpp
#include <iostream>
#include <vector>
using namespace std;


class myObject {
    private:
        int soy = 5;
    public:

        myObject(int y) {
            cout << "object1 initializerd" << endl;
            cout << "Given constructor integer value is: " << y << endl;
        }

        void soyAdmen() {
            cout << 5+5 << endl;
        }
};