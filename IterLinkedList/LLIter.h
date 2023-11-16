#ifndef ITERLINKEDLIST_LLITER_H
#define ITERLINKEDLIST_LLITER_H

#include "Node.h"
template <class T>
class LLIter : Iterator {
private:
    Node<T> *node;
    // int iterationComplete; унаследовано от Iterator
public:
    Iterator();

    virtual void next() = 0;
    virtual void reset() = 0;

    virtual T& data() = 0;
};


template <class T>
T& LLIter<T>::data() {
    return *(node->data);
}


#endif //ITERLINKEDLIST_LLITER_H
