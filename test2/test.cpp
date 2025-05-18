
// my_lib.cpp
#include <iostream>

using namespace std;

struct Head {
    int a;
    Head *next;
};



int main() {
    Head *head = new Head;
    head->a = 1;
    head->next = nullptr;
    Head *current = head;
    for (int i = 0; i < 5; ++i) {
        Head *newNode = new Head;
        newNode->a = i + 2;
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }
    // PRINT out the linked list vals
    current = head;
    while (current != nullptr) {
        cout << current->a << " ";
        current = current->next;
    }
    return 0;
}
