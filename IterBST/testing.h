#ifndef ITERBST_TESTING_H
#define ITERBST_TESTING_H

#include "BST.h"

// 0
//  \
//   5
//    \
//    20
//   /  \
//  15   31
//  /
// 10

BST<int> createBST() {
    BST<int> bst = BST<int>(new TreeNode<int>(0));
    bst.insert(5);
    bst.insert(20);
    bst.insert(31);
    bst.insert(15);
    bst.insert(10);
    return bst;
}

void eqNotEqTest() {
    BST<int> bst = createBST();
    IterBST<int> iter1 = bst.begin();
    IterBST<int> iter2 = bst.begin();
    if (!(iter1 == iter2)) throw std::runtime_error("LLIter == LLIter returns wrong value");
    ++iter2;
    if (!(iter1 != iter2)) throw std::runtime_error("LLIter != LLIter returns wrong value");
}


void asteriskTest() {
    BST<int> bst = createBST();
    IterBST<int> iter = bst.begin();
    *iter = 11;
    if (*iter != 11) throw std::runtime_error("asterisk error");
}

void ppTest() {
    BST<int> bst = createBST();
    IterBST<int> iter = bst.begin();
    if (*(++iter) != 15) throw std::runtime_error("++iter error.");
}

void endTest() {
    BST<int> bst = createBST();
    IterBST<int> endIter = bst.end();
    IterBST<int> iter = bst.begin();
    for (int i = 0; i<bst.getSize(); i++)
        ++iter;
    if (iter != endIter) throw std::runtime_error("Failed to get endIter using prefix increment");
}

void testing() {
    asteriskTest();
    eqNotEqTest();
    ppTest();
    endTest();
}

#endif //ITERBST_TESTING_H
