// автор: Артамонов Илья

#ifndef ITERLINKEDLIST_TESTING_H
#define ITERLINKEDLIST_TESTING_H

#include "LinkedList.h"
#include <exception>

// создание связанного списка:
// 1 - 2 - 3 ... 10
LinkedList<int> createLL() {
    LinkedList<int> ll;
    for (int i=1; i<=10; i++)
        ll.insertRear(i);
    return ll;
}

// проверка правильности выполнения оператора префиксного инкремента
void ppTest() {
    LinkedList<int> ll = createLL();
    LLIter<int> iter = ll.begin();
    if (*(++iter) != 2) throw std::runtime_error("++LLIter returns incorrect value");
    if (*iter != 2) throw std::runtime_error("++LLIter doesnt move iter to next value");
}

// проверка операций равенства и неравенства
void eqNotEqTest() {
    LinkedList<int> ll = createLL();
    LLIter<int> iter1 = ll.begin();
    LLIter<int> iter2 = ll.begin();
    if (!(iter1 == iter2)) throw std::runtime_error("LLIter == LLIter returns wrong value");
    ++iter2;
    if (!(iter1 != iter2)) throw std::runtime_error("LLIter != LLIter returns wrong value");
}

// проверка выполнения операции звездочки для LLIter
void asteriskTest() {
    bool doesntThrow = false;
    LinkedList<int> ll = createLL();
    try {
        LLIter<int> endIter = ll.end();
        *endIter;
        doesntThrow = true;
        throw std::runtime_error("*endIter doesnt throw exception");
    }
    catch (std::exception& exception) {
        if (doesntThrow) throw std::runtime_error(exception.what());
    }
}

// дойти до последнего элемента и сравнить его с LinkedList.end()
void endTest() {
    LinkedList<int> ll = createLL();
    LLIter<int> endIter = ll.end();
    LLIter<int> iter = ll.begin();
    for (int i = 0; i<10; i++)
        ++iter;
    if (endIter != iter) throw std::runtime_error("iter != endIter");
}

// вызов всех функций тестирования
void testing() {
    ppTest();
    eqNotEqTest();
    asteriskTest();
    endTest();
}

#endif //ITERLINKEDLIST_TESTING_H
