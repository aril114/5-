#ifndef BST_TESTING_H
#define BST_TESTING_H

#endif //BST_TESTING_H

#include "BST.h"
#include "TreeNode.h"

// 0
//  \
//   5
//    \
//    20
//   /  \
//  15   31
//  /
// 10

BST<int>* createBST() {
    BST<int>* bst = new BST<int>(new TreeNode<int>(0));
    bst->insert(5);
    bst->insert(20);
    bst->insert(31);
    bst->insert(15);
    bst->insert(10);
    return bst;
}

bool removeTest() {
    BST<int>* bst = createBST();
    BST<int> bst2 = *bst; // здесь будет вызван конструктор копирования
    int originalSize = bst->getSize();
    bst->remove(bst->find(10));
    if (bst->getSize() != originalSize-1) return false;
    int* bstArray = btToArray(bst->getRoot());

    int expectedValues[5] = { 15, 31, 20, 5, 0 };

    delete bst;

    return std::equal(bstArray, bstArray+5, expectedValues);

    /* for (int i = 0; i<5; i++) {
        std::cout << "bstArray[" << i << "] = " << bstArray[i] << "\n";
    }*/
}

bool findTest() {
    BST<int> *bst = createBST();
    int values[6] = { 0, 5, 20, 31, 15, 10 };
    TreeNode<int> *node;
    for (int value : values) {
        node = bst->find(value);
        if (node->getData() != value) {
            delete bst;
            return false;
        }
    }

    bool result = bst->find(-1) == nullptr;
    delete bst;
    return result;
}

bool insertTest() {
    BST<int>* bst = createBST();
    int value = 32;
    bst->insert(32);
    TreeNode<int> *expectedParent = bst->find(31);
    bool result = expectedParent->getR() != bst->find(32);
    delete bst;
    return result;
}

void testing() {
    if (!removeTest()) throw std::runtime_error("removeTest failed");
    if (!findTest()) throw std::runtime_error("findTest failed");
    if (!insertTest()) throw std::runtime_error("insertTest failed");
}