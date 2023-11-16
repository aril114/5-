#include <iostream>
#include "TreeNode.h"
#include <algorithm>
#include <cstring>


// выводит дерево по указателю на корень
template <typename T>
void printTree(TreeNode<T>* root) {
    std::cout << root->getData();
    TreeNode<T> *fc = root->getL();
    TreeNode<T> *sc = root->getR();
    if (fc != nullptr) {
        std::cout << " l: " << fc->getData();
    }
    if (sc != nullptr) {
        std::cout << " r: " << sc->getData();
    }
    if (fc == nullptr && sc == nullptr) std::cout << " - leaf";
    std::cout << "\n";
    if (fc != nullptr) printTree(fc);
    if (sc != nullptr) printTree(sc);
}

// 0
//  \
//   5
//    \
//    20
//   /  \
//  15   31
//  /
// 10

TreeNode<int>* createBST() {
    TreeNode<int>* root = new TreeNode<int>(0);
    addToBST(root, 5);
    addToBST(root, 20);
    addToBST(root, 31);
    addToBST(root, 15);
    addToBST(root, 10);
    return root;
}

bool createBSTTest() {
    TreeNode<int>* root = createBST();
    int* bstArray = toArray(root);
    delTree(root);

    int array[6] = { 10, 15, 31, 20, 5, 0 };    

    bool result = std::equal(array, array+6, bstArray);
    // в динамическую память помещается только bstArray
    // только его память и освобождаем
    delete[] bstArray;
    return result;
}

// создается дерево :
//            0
//           / \
//          1   2
//         / \
//        3   4

TreeNode<int>* createTree() {
    TreeNode<int>* root = new TreeNode<int>(0);
    root->setL(new TreeNode<int>(1));
    root->setR(new TreeNode<int>(2));
    root->getL()->setL(new TreeNode<int>(3));
    root->getL()->setR(new TreeNode<int>(4));
    return root;
}

// 1
//  \
//   2
//    \
//     3
//      \
//      ...
//        \
//        10

TreeNode<int>* createDegenerateBST() {
    TreeNode<int>* root = new TreeNode<int>(1);
    {
        TreeNode<int>* node = root;
        for (int i = 2; i <= 10; i++) {
            node->setR(new TreeNode<int>(i));
            node = node->getR();
        }
    }
    return root;
}

bool createTreeTest() {
    TreeNode<int>* root = createTree();
    int* treeArray = toArray(root);
    delTree(root);

    int array[5] = { 3, 4, 1, 2, 0 };
    bool result = std::equal(array, array+5, treeArray);
    delete[] treeArray;
    return result;

}

bool copyTreeTest() {
    TreeNode<int>* root1 = createTree();
    TreeNode<int>* root2 = copyTree(root1);
    
    int* array1 = toArray(root1);
    int* array2 = toArray(root2);
    
    delTree(root1);
    delTree(root2);
    
    bool result = std::equal(array1, array1+5, array2);
    
    delete[] array1;
    delete[] array2;
    
    TreeNode<int>* degenerateTree = createDegenerateBST();
    TreeNode<int>* degenerateTreeCopied = copyTree(degenerateTree);
    
    array1 = toArray(degenerateTree);
    array2 = toArray(degenerateTreeCopied);
    
    delTree(degenerateTree);
    delTree(degenerateTreeCopied);
    
    result = result ? std::equal(array1, array1+10, array2) : false;
    
    delete[] array1;
    delete[] array2;
    
    return result;
}

// вспомогательная функция для toArrayTest (основной алгоритм)
// LRN
// bool btEqualsToArray(TreeNode<int>* node, int* array, int& index) {
//     bool result = true;
//     TreeNode<int>* firstChild = node->getL();
//     if (firstChild != nullptr) {
//         result = btEqualsToArray(firstChild, array, index);
//         if (result == false) return false;
//     }
//     TreeNode<int>* secondChild = node->getR();
//     if (secondChild != nullptr) {
//         result = btEqualsToArray(secondChild, array, index);
//         if (result == false) return false;
//     }
//     if (node->getData() != array[index])
//         return false;
//     // if (node->getData() != array[index]) {
//     //     std::cout << "Error!\n";
//     //     exit(1);
//     // }
//     index++;
// }

// bool btEqualsToArrayWrapper(TreeNode<int>* node, int* array, int arraySize) {
//     int index = 0;
//     bool returnVal = btEqualsToArray(node, array, index);
//     return (returnVal == true && index == arraySize) ? true : false;
// }


// проверка функции toArray
bool toArrayTest() {
    TreeNode<int>* root = createTree();
    int* treeArray = toArray(root);
    delTree(root);

    int trueValues[5] = { 3, 4, 1, 2, 0};

    bool result = std::equal(treeArray, treeArray+5, trueValues);

    
    delete[] treeArray;

    return result;
}

// 0
//  \
//   5
//    \
//    20
//   /  \
//  15   31
//  /
// 10

bool succTest() {
    // проверка на обычном бинарном дереве поиска
    {
        TreeNode<int>* bstRoot = createBST();
        TreeNode<int>* answer = succ(btSearch(bstRoot, 15), bstRoot);
        if (answer != btSearch(bstRoot, 20)) return false;
        
        delTree(bstRoot);
    }
    
    // проверка на дереве из одного узла
    {
        TreeNode<int>* node = new TreeNode<int>(1);
        if (succ(node, node) != nullptr) return false;        
        delete node;
    }
    
    {
        // проверка на вырожденном дереве
        TreeNode<int> *root = createDegenerateBST();
        TreeNode<int> *node = btSearch(root, 3);
        if (succ(node, root) != btSearch(root, 4))
            return false;
        
        delTree(root);
    }
    
    // проверка на nullptr
    try {
        succ((TreeNode<int>* )nullptr, (TreeNode<int>* )nullptr);
    }
    catch (std::exception& exception) {
            return true;
    }
    return false;
}

bool removeTest() {
	int origValues[6] = { 10, 15, 31, 20, 5, 0 };


	int gotValues[4];
	for (int i = 0; i<5; i++) {
		TreeNode<int>* root = createBST();

		std::memcpy(gotValues, origValues, sizeof(int)*i);
		std::memcpy(gotValues+i, origValues+i+1, sizeof(int)*(5-i-1));

		remove((btSearch(root, origValues[i])), root);
		int* bstArray = toArray(root);
		bool result = std::equal(gotValues, gotValues+4, bstArray);
		delete[] bstArray;
		delTree(root);
		if (!result) {
	//		delete[] gotValues;
			return false;
		}
	}
    TreeNode<int>* root = createBST();
    TreeNode<int>* child = root->getR();
    remove(root, root);
    int* bstArray = toArray(child);
    int resultValues[5] = { 10, 15, 31, 20, 5 };

    bool result = std::equal(resultValues, resultValues+5, bstArray);
    delete[] bstArray;
	//delete[] gotValues;
	return result;
}

void test() {
    bool testFailed = false;

    if (!toArrayTest()) {
        std::cout << "ошибка при проверке функции toArray\n";
        testFailed = true;
    }

    if (!createTreeTest()) {
        std::cout << "ошибка при проверке функции createTree\n";
        testFailed = true;
    }

    if (!createBSTTest()) {
        std::cout << "ошибка при проверке функции createBST\n";
        testFailed = true;
    }
    
    if (!succTest()) {
        std::cout << "ошибка при проверке функции succ\n";
        testFailed = true;
    }
    
    if (!copyTreeTest()) {
        std::cout << "ошибка при проверке функции copyTreeTest\n";
        testFailed = true;
    }

	if (!removeTest()) {
		std::cout << "ошибка при проверке функции removeTest\n";
        testFailed = true;
	}
        
    if (testFailed)
        exit(1);
}
