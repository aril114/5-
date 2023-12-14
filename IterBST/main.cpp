#include <iostream>
#include "testing.h"

int main() {
    testing();

    BST<int> bst = createBST();

    for (int el: bst) // создаются неявные итераторы
        std::cout << el << "\n";
}
