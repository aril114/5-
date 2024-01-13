#ifndef ITERLINKEDLIST_NODE_H
#define ITERLINKEDLIST_NODE_H

#include <cstddef>

template <typename T>
class Node
{
private:
    // next указывает на адрес
    // следующего узла
    Node<T> *next;
public:
    // открытые данные
    T data;

    // конструктор
    Node (const T& item, Node<T>* ptrnext = nullptr);

    // методы модификации списка
    void insertAfter(Node<T> *p);
    Node<T> *deleteAfter();

    // получение адреса следующего узла
    Node<T> *nextNode() const;
};

using namespace std;

// конструктор. инициализация данных и указателя
template <typename T>
Node<T>::Node(const T& item, Node<T>* ptrnext) :
        data(item), next(ptrnext)
{}

// возвратить закрытый член next
template <typename T>
Node<T> *Node<T>::nextNode() const
{
    return next;
}

// вставить узел p после текущего узла
template <typename T>
void Node<T>::insertAfter(Node<T> *p)
{
    next = p;
}

// удалить узел, следующий за текущим, и возвратить его адрес
template <typename T>
Node<T> *Node<T>::deleteAfter()
{
    // сохранить адрес удаляемого узла
    Node<T> *tempPtr = next;

    // если нет следующего узла, возвратить nullptr
    if (next == nullptr)
        return nullptr;

    // текущий узел указывает на узел, следующий за tempPtr
    next = tempPtr->next;

    // возвратить указатель на несвязанный узел
    return tempPtr;
}

#endif //ITERLINKEDLIST_NODE_H
