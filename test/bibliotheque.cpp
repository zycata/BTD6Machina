#include <iostream>
#include <cmath>
#include "bibliotheque.h"

namespace bibliotheque {
    int yap() {
        std::cout << "Hello from bibliotheque" << std::endl;
        return 5;
    }

    void test() {
        std::cout << "Test function in bibliotheque" << std::endl;
    }

}


using namespace std;
using namespace bibliotheque;

int roundToNearestFive(float value) {
    return static_cast<int>(5 * round(value / 5.0f));
}

int roundToNearest5(int num, float multiplier) {
    float value = num * multiplier;
    return static_cast<int>(5 * round(value / 5.0f));
}
int main() {
    
    cout << roundToNearest5(200,  1.08) << endl;
    cout << roundToNearestFive(244.0) << endl;
    cout << roundToNearestFive(250.0) << endl;
    int a[2] = {1, 2};
    cout << a[3] << endl;
    return 0;

}