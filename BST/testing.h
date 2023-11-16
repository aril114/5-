#ifndef BST_TESTING_H
#define BST_TESTING_H

#include <cstring>
#include <stdexcept>
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
    int origValues[6] = { 10, 15, 31, 20, 5, 0 };
    int expValues[4];

    // в цикле из дерева удаляются по очереди все элементы origValues,
    // кроме последнего, и проверяется, получилось ли дерево таким, как ожидалось
    for (int i = 0; i<5; i++) {
        BST<int>* bst = createBST();

        // сначала копируется i первых чисел из массива origValues
        std::memcpy(expValues, origValues, sizeof(int) * i);

        // затем, начиная с i+1-го элемента, копируются оставшиеся 5-i-1
        std::memcpy(expValues + i, origValues + i + 1, sizeof(int) * (5 - i - 1));

        bst->remove(bst->find(origValues[i]));
        int* bstArray = btToArray(bst->getRoot());

        // сравнивается 4 элемента
        bool result = std::equal(expValues, expValues + 4, bstArray);
        delete[] bstArray;
        delete bst;
        if (!result) {
            return false;
        }
    }
    return true;
}

bool findTest() {
    BST<int> *bst = createBST();
    int values[6] = { 0, 5, 20, 31, 15, 10 };
    TreeNode<int> *node;
    for (int value : values) {
        node = bst->find(value);
        if (node == nullptr) {
            delete bst;
            return false;
        }
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
    // добавление потомка корню
    {
        unsigned int initialSize = bst->getSize();
        bst->insert(-1);

        if (bst->getSize() != initialSize + 1) {
            delete bst;
            return false;
        }

        TreeNode<int> *expectedParent = bst->getRoot();
        bool result = expectedParent->getL() == bst->find(-1);
        if (!result) {
            delete bst;
            return result;
        }
    }
    // добавление листа
    bst->insert(9);
    TreeNode<int> *expectedParent = bst->find(10);
    bool result = expectedParent->getL() == bst->find(9);
    if (!result) {
        delete bst;
        return result;
    }
    // добавление обычного узла
    bst->insert(4);
    expectedParent = bst->find(5);
    result = expectedParent->getL() == bst->find(4);
    delete bst;
    return result;
}

void testing() {
    if (!removeTest()) throw std::runtime_error("removeTest failed");
    if (!findTest()) throw std::runtime_error("findTest failed");
    if (!insertTest()) throw std::runtime_error("insertTest failed");
}

#endif //BST_TESTING_H
