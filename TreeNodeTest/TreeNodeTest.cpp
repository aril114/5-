#include "testing.h"

int main()
{
    // создается дерево :
    //            0
    //           / \
    //          1   2
    //         / \
    //        3   4
    test();
    
    /*TreeNode<int>* root = createTree();

    // дерево выводится
    // printTree(root);

    // NRL<int>(root, [](TreeNode<int> *xnode){ std::cout << xnode->getData() << "\n";  });

    int size = 0;
    treeCount(root, size);

    std::cout << "nodes: " << size << "\n";

    int* array = toArray(root);

    std::cout << "array: ";
    for (int i = 0; i < size; i++)
        std::cout << array[i] << " ";
    std::cout << "\n";

    TreeNode<int>* bstRoot = createBST();
    
    std::cout << "bst:\n";

    printTree(bstRoot);
    
    {
        TreeNode<int>* node = bstRoot;
        TreeNode<int>* biggerNode;
	    while (true) {
		std::cout << "Поиск значения больше " << node->getData() << ".\n";
		biggerNode = succ(node, bstRoot);
		if (biggerNode == nullptr) {
			std::cout << "Большего значения нет.\n";
			break;
		}
		std::cout << biggerNode->getData() << "\n";
		node = biggerNode;
	    }
    }
    
    std::cout << "height: " << btHeight(bstRoot) << "\n";
    
    TreeNode<int> *newTree = copyTree(root);
    
    std::cout << "старое дерево:\n";
    printTree(root);
    std::cout << "новое дерево:\n";
    printTree(newTree);
    
    // освобождается память, занятая деревом
    delTree(root);
    delTree(bstRoot);*/
}