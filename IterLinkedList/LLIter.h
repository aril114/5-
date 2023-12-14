// автор: Артамонов Илья

#ifndef ITERLINKEDLIST_LLITER_H
#define ITERLINKEDLIST_LLITER_H

#include "Node.h"
#include "LinkedList.h"
#include "Iterator.h"

// итератор для связанного списка
template <typename T>
class LLIter : public Iterator<T> {
private:
    Node<T>* node;
public:
    LLIter(Node<T>* node);
    // префиксный инкремент
    Iterator<T>& operator++() override;
    // возвращает данные
    T& operator*() override;
    // проверка на равенство
    bool operator==(const Iterator<T>&) const override;
    // проверка на неравенство
    bool operator!=(const Iterator<T>&) const override;
};

// конструктор по указателю на узел
template <typename T>
LLIter<T>::LLIter(Node<T> *node) {
    this->node = node;
}

// возвращает данные
template <typename T>
T& LLIter<T>::operator*() {
    if (this->node == nullptr) throw std::runtime_error("Tried to get value of nullptr node");
    return this->node->data;
}

// сравнивает два элемента
template <typename T>
bool LLIter<T>::operator==(const Iterator<T>& iter) const {
    // dynamic_cast бросает исключение если преобразование не удается
    return this->node == dynamic_cast<const LLIter<T>&>(iter).node;
}

// проверка на неравенство
template <typename T>
bool LLIter<T>::operator!=(const Iterator<T>& iter) const {
    return this->node != dynamic_cast<const LLIter<T>&>(iter).node;
}

// префиксный инкремент
template <typename T>
Iterator<T>& LLIter<T>::operator++() {
    this->node = this->node->nextNode();
    return *this;
}

#endif //ITERLINKEDLIST_LLITER_H