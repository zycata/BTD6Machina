#include <iostream>

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


/*
using namespace bibliotheque;
int main() {
    std::cout << "Hey, World!" << std::endl;
    std::cout << "yap: " << yap() << std::endl;
    return 0;
}*/