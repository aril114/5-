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

#endif //ITERBST_TESTING_H
