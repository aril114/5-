#ifndef ITERLINKEDLIST_ITERATOR_H
#define ITERLINKEDLIST_ITERATOR_H

template <class T>
class Iterator {
protected:
    // это поле устанавливается в единицу при выходе за верхнюю границу списка
    int iterationComplete;

public:
    Iterator();

    virtual void next() = 0;
    virtual void reset() = 0;

    virtual T& data() = 0;

    virtual int endOfList() const;
};

template <class T>
int Iterator<T>::endOfList() const {
    return iterationComplete;
}


#endif //ITERLINKEDLIST_ITERATOR_H
