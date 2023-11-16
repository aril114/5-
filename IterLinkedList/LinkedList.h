#ifndef ITERLINKEDLIST_LINKEDLIST_H
#define ITERLINKEDLIST_LINKEDLIST_H

#include <cstddef>
#include "node.h"

template <class T>
class LinkedList
{
private:
    // указатели для доступа к началу и концу списка
    Node<T> *front, *rear;

    // используются для извлечения, вставки и удаления данных
    Node<T> *prevPtr, *currPtr;

    // число элементов в списке
    int size;

    // положение в списке. используется методом reset
    int position;
    // закрытые методы создания и удаления узлов
    // void freeNode(Node<T> *p);

    // копирует список L в текущий список
    void copyList(const LinkedList<T>& L);

public:
    // конструктор
    LinkedList(void);
    // LinkedList(const LinkedList<T>& L);

    // деструктор
    ~LinkedList(void);

    // оператор присваивания
    // LinkedList<T>& operator= (const LinkedList<T>& L);

    // проверка состояния списка
    int listSize(void) const;
    int listEmpty(void) const;

    // методы прохождения списка
    void reset(int pos = 0);
    void next(void);
    int endOfList(void) const;

    // методы вставки
    void insertFront(const T& item);
    void insertRear(const T& item);
    void insertAt(const T& item);

    // методы удаления
    void deleteFront(void);
    void deleteAt(void);

    // возвратить/изменить данные
    T& data(void);

    // очистка списка
    void clearList(void);

    // возвращает position
    int currentPosition(void) const;

    // возвращает список в текстовом виде, разделяя элементы списка пробелами
    string toString() const;

};

#include <iostream>

using namespace std;

// возвращает список в текстовом виде, разделяя элементы списка пробелами
template <class T>
string LinkedList<T>::toString() const {
    if (size == 0) {
        return "Список пуст.";
    }
    Node<T> *ptr;
    string str;
    for (ptr = front; ptr->nextNode() != NULL; ptr = ptr->nextNode()) {
        str.append(to_string(ptr->data));
        str.append(" ");
    }
    str.append(to_string(ptr->data));
    return str;
}

// удалить первый узел списка
template <class T>
void LinkedList<T>::deleteFront()
{
    // убедиться в том, что список не пуст
    if (front == NULL)
    {
        cerr << "front = NULL!" << endl;
        exit(1);
    }
    Node<T> *oldfront = front;
    // передвинуть голову к следующему злу
    front = oldfront->nextNode();
    size--;
    if (position > -1)
        position--;
    delete oldfront;
}

// найти хвост списка и добавить item
template <class T>
void LinkedList<T>::insertRear(const T& item)
{
    Node<T> *newNode;

    // если список пуст, вставить item в начало
    if (size == 0)
        insertFront(item);
    else
    {
        newNode = new Node(item);
        rear->insertAfter(newNode);
        rear = newNode;
    }
    size++;
}

// вставка элемента в начало списка
template <class T>
void LinkedList<T>::insertFront(const T& item)
{
    // создание нового узла, чтобы он указывал
    // на первоначальную голову списка
    // изменение головы списка
    Node<T> *newFront = new Node(item, front);
    front = newFront;
    if (position > -1) {
        position++;
    }
    if (size == 0) {
        rear = front;
    }
    size++;

}

// создать пустой список
template <class T>
LinkedList<T>::LinkedList(void): front(NULL), rear(NULL),
                                 prevPtr(NULL), currPtr(NULL), size(0), position(-1)
{}

// копировать L в текущий список (предполагается пустым)
template <class T>
void LinkedList<T>::copyList(const LinkedList<T>& l)
{
    // p - указатель на l
    Node<T> *p = l.front;
    int pos;

    // вставлять каждый элемент из l в конец текущего объекта
    while (p != NULL)
    {
        insertRear(p->data);
        p = p->nextNode();
    }

    // выход, если список пустой
    if (position == -1)
        return;

    // переустановить prevPtr и currPtr в новом списке
    prevPtr = NULL;
    currPtr = front;
    for (pos = 0; pos != position; pos++)
    {
        prevPtr = currPtr;
        currPtr = currPtr->nextNode();
    }
}

// clearList проходит связанный список и уничтожает все узлы
template <class T>
void LinkedList<T>::clearList(void)
{
    Node<T> *currPosition, *nextPosition;

    currPosition = front;
    while(currPosition != NULL)
    {
        // получить адрес следующего узла и удалить текущий
        nextPosition = currPosition->nextNode();
        delete currPosition;
        currPosition = nextPosition;	// перейти к следующему узлу
    }
    front = rear = NULL;
    prevPtr = currPtr = NULL;
    size = 0;
    position = -1;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    clearList();
}

// reset устанавливает текущее положение прохождения в позицию,
// обозначенную параметром pos
template <class T>
void LinkedList<T>::reset(int pos)
{
    int startPos;

    // если список пустой, выход
    if (front == NULL)
        return;

    // если положение задано не верно, закончить программу
    if (pos < 0 || pos > size-1)
    {
        cerr << "reset: неверно задано положение: " << pos
             << endl;
        return;
    }

    // установить механизм прохождения в pos
    if(pos == 0)
    {
        // перейти в начало списка
        prevPtr = NULL;
        currPtr = front;
        position = 0;
    }
    else
        // переустановить currPtr, prevPtr и startPos
    {
        currPtr = front->nextNode();
        prevPtr = front;
        startPos = 1;
        // передвигаться вправо до pos
        for(position=startPos; position != pos; position++)
        {
            // передвинуть оба указателя прохождения вперед
            prevPtr = currPtr;
            currPtr = currPtr->nextNode();
        }
    }
}

// переустановить prevPtr и currPtr вперед на один узел
template <class T>
void LinkedList<T>::next(void)
{
    // выйти, если конец списка или
    // список пустой
    if(currPtr != NULL)
    {
        // переустановить два указателя на один узел вперед
        prevPtr = currPtr;
        currPtr = currPtr->nextNode();
        position++;
    }
}

// возвратить ссылку на данные текущего узла
template <class T>
T& LinkedList<T>::data(void)
{
    // ошибка, если список пустой или прохождение закончено
    if (size == 0 || currPtr == NULL)
    {
        cerr << "data: неверная ссылка!" << endl;
        exit(1);
    }
    return currPtr->data;
}

// вставка item в текущую позицию списка
template <class T>
void LinkedList<T>::insertAt(const T& item)
{
    Node<T> *newNode;

    // два случая: вставка в начало или внутрь списка
    if (prevPtr == NULL)
    {
        // вставка в начало списка. помещает также
        // узел в пустой список
        newNode = new Node(item, front);
        front = newNode;
    }
    else
    {
        // вставка внутрь списка. помещает узел после prevPtr
        newNode = new Node(item);
        prevPtr->insertAfter(newNode);
    }

    // при prevPtr == rear, имеем вставку в пустой список
    // или в хвост непустого списка; обновляет rear и position
    if (prevPtr == rear)
    {
        rear = newNode;
        position = size;
    }

    // обновить currPtr и увеличить size
    currPtr = newNode;
    size++;
}

// удаление узла в текущей позиции списка
template <class T>
void LinkedList<T>::deleteAt(void)
{
    Node<T> *p;

    // ошибка, если список пустой или конец списка
    if (currPtr == NULL)
    {
        cerr << "Ошибка удаления!" << endl;
        exit(1);
    }

    // удалять можно только в начале и внутри списка
    if (prevPtr == NULL)
    {
        // сохранить адрес начала, но не связывать его. если это -
        // последний узел, присвоить front значение NULL
        p = front;
        front = front->nextNode();
    }
    else
        // не связывать внутренний узел после prevPtr.
        // запомнить адрес
        p = prevPtr->deleteAfter();

    // если хвост удален, адрес нового хвоста в prevPtr,
    // а position уменьшается на 1
    if (p == rear)
    {
        rear = prevPtr;
        position--;
    }

    // установить currPtr на послендий удаленный узел.
    // если p - последний узел в списке,
    // currPtr становится равным NULL
    currPtr = p->nextNode();

    // освободить узел и уменьшить значение size
    // freeNode(p);
    delete p;
    size--;
}

// возвращает размер списка
template <class T>
int LinkedList<T>::listSize(void) const {
    return size;
}

// проверяет, пуст ли список
template <class T>
int LinkedList<T>::listEmpty(void) const {
    return (front == NULL);
}

// проверяет, ссылается ли currPtr на NULL
template <class T>
int LinkedList<T>::endOfList(void) const {
    return currPtr == NULL;
}

// возвращает position
template <class T>
int LinkedList<T>::currentPosition(void) const {
    return position;
}

#endif //ITERLINKEDLIST_LINKEDLIST_H
