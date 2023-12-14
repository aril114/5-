#ifndef ITERBST_ITERBST_H
#define ITERBST_ITERBST_H

#ifndef ITERLINKEDLIST_LLITER_H
#define ITERLINKEDLIST_LLITER_H

#include "TreeNode.h"
#include "Iterator.h"

// итератор для связанного списка
template <typename T>
class IterBST : public Iterator<T> {
private:
    TreeNode<T>* node;
    TreeNode<T>* root;
public:
    IterBST(TreeNode<T>* node, TreeNode<T> *root);
    // префиксный инкремент
    Iterator<T>& operator++() override;
    // возвращает данные
    T& operator*() override;
    // проверка на равенство
    bool operator==(const Iterator<T>&) const override;
    // проверка на неравенство
    bool operator!=(const Iterator<T>&) const override;

};


template <typename T>
IterBST<T>::IterBST(TreeNode<T> *node, TreeNode<T> *root) {
    this->node = node;
    this->root = root;
}

// возвращает данные
template <typename T>
T& IterBST<T>::operator*() {
    if (this->node == nullptr) throw std::runtime_error("Tried to get value of nullptr node");
    return this->node->data;
}

// проверка на равенство
template <typename T>
bool IterBST<T>::operator==(const Iterator<T>& iter) const {
    // dynamic_cast бросает исключение если преобразование не удается
    IterBST<T> other = dynamic_cast<const IterBST<T>&>(iter);
    return ((this->node == other.node) && (this->root == other.root));
}

// проверка на неравенство
template <typename T>
bool IterBST<T>::operator!=(const Iterator<T>& iter) const {
    // dynamic_cast бросает исключение если преобразование не удается
    IterBST<T> other = dynamic_cast<const IterBST<T>&>(iter);
    return ((this->node != other.node) || (this->root != other.root));
}

// префиксный инкремент
template <typename T>
Iterator<T>& IterBST<T>::operator++() {
    if (node == root) node = nullptr;
    else {
        this->node = this->node->nextNode(root);
    }
    return *this;
}

#endif //ITERLINKEDLIST_LLITER_H


#endif //ITERBST_ITERBST_H
