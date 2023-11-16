#ifndef BST_BST_H
#define BST_BST_H

#endif //BST_BST_H

#include "TreeNode.h"

template <typename T>
class BST {
private:
    // корень
    TreeNode<T>* root;
    // количество узлов в дереве
    unsigned int size;

public:
    // конструктор по указателю на корень
    BST(TreeNode<T>* root);
    // получение количества узлов
    unsigned int getSize() const;
    // добавление узла
    void insert(T value);
    // удаление узла
    void remove(TreeNode<T>* toRemove);
    // поиск узла
    TreeNode<T>* find(T query) const;
    // получение корня
    TreeNode<T>* getRoot() const;

    // конструктор копирования
    BST(const BST<T>& bst);
    // деструктор
    ~BST();
    // задание нового корня
    void setRoot(TreeNode<T> *newRoot);

    // конструктор перемещения
    BST(BST<T>&& other);

    // оператор присваивания копированием
    BST& operator=(const BST& other);

    // Оператор присваивания перемещением (move assignment)
    BST& operator=(BST<T>&& other);

};

// Оператор присваивания перемещением (move assignment)
template <typename T>
BST<T> &BST<T>::operator=(BST<T>&& other)
{
    if (this == &other)
        return *this;


    delBt(root);

    root = other.getRoot();
    size = other.size;

    other.setRoot(new TreeNode<T>);
    delete other;

    return *this;
}


// оператор присваивания копированием
template<typename T>
BST<T> &BST<T>::operator=(const BST &other) {
    if (this == other) return *this;

    delBt(root);

    root = copyBt(other.getRoot());
    size = other.getSize();

    return *this;
}


// задание нового корня
template<typename T>
void BST<T>::setRoot(TreeNode<T> *newRoot) {
    root = newRoot();
    size = btCount(newRoot);
}

// конструктор перемещения
template <typename T>
BST<T>::BST(BST<T>&& other)
{
    root = other.getRoot();
    size = other.getSize();
    other.setRoot(new TreeNode<T>);
    delete other;
}


// конструктор копирования
template <typename T>
BST<T>::BST(const BST<T>& bst) {
    root = copyBt(bst->getRoot());
    size = btCount(root);
}

// получение корня
template <typename T>
TreeNode<T>* BST<T>::getRoot() const { return root; };

// конструктор по узлу
template <typename T>
BST<T>::BST(TreeNode<T>* root) {
    if (root == nullptr)
        throw std::invalid_argument("root не должен быть nullptr.");
    this->root = root;
    size = 1;
}

// получение количества узлов
template <typename T>
unsigned int BST<T>::getSize() const { return size; }

// добавление нового узла по значению этого узла
template <typename T>
void BST<T>::insert(T value) {
    addToBST(root, value);
    size++;
}

// поиск узла
template <typename T>
TreeNode<T>* BST<T>::find(T query) const {
    return btSearch(root, query);
}

// удаление узла
template <typename T>
void BST<T>::remove(TreeNode<T>* toRemove) {
    btRemove(toRemove, root);
    size--;
}

// деструктор
template<typename T>
BST<T>::~BST() {
    delBt(root);
}