#include <iostream>

#include "bibliotheque.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "yap: " << bibliotheque::yap() << std::endl;
    system("pause");
    std::cout << "Press any key to continue..." << std::endl;
    bibliotheque::test();
    return 0;
}