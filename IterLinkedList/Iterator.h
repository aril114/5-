// автор: Артамонов Илья

#ifndef ITERLINKEDLIST_ITERATOR_H
#define ITERLINKEDLIST_ITERATOR_H

// абстрактный класс итератора
template <typename T>
class Iterator {
public:
    // переход на следующий элемент
    virtual Iterator& operator++() = 0;
    // возвращает ссылку на элемент
    virtual T& operator*() = 0;
    virtual bool operator==(const Iterator<T>&) const = 0;
    virtual bool operator!=(const Iterator<T>&) const = 0;
};


#endif //ITERLINKEDLIST_ITERATOR_H
