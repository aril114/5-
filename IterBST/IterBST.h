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
    Iterator<T>& operator++() override;
    T& operator*() override;
    bool operator==(const Iterator<T>&) const override;
    bool operator!=(const Iterator<T>&) const override;

};


template <typename T>
IterBST<T>::IterBST(TreeNode<T> *node, TreeNode<T> *root) {
    this->node = node;
    this->root = root;
}

template <typename T>
T& IterBST<T>::operator*() {
    if (this->node == nullptr) throw std::runtime_error("Tried to get value of nullptr node");
    return this->node->data;
}

template <typename T>
bool IterBST<T>::operator==(const Iterator<T>& iter) const {
    // dynamic_cast бросает исключение если преобразование не удается
    return this->node == dynamic_cast<const IterBST<T>&>(iter).node;
}

template <typename T>
bool IterBST<T>::operator!=(const Iterator<T>& iter) const {
    return this->node != dynamic_cast<const IterBST<T>&>(iter).node;
}

template <typename T>
Iterator<T>& IterBST<T>::operator++() {
    this->node = this->node->nextNode(root);
    return *this;
}

#endif //ITERLINKEDLIST_LLITER_H


#endif //ITERBST_ITERBST_H
