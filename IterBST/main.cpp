#include <iostream>
#include "testing.h"
#include "BST.h"

int main() {
    BST<int> bst = createBST();

    for (int el: bst)
        std::cout << el << "\n";

    std::cout << "end: " << *bst.end() << "\n";
    std::cout << "begin: " << *bst.begin() << "\n";
}
