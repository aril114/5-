

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <iostream>
#include <cstdlib>

// min heap
template <class T>
class Heap {
private:
    // hlist указывает на массив, который может быть динамически создан
    // конструктором (inArray == 0) или передан как параметр (inArray == 1)
    T *hlist;
    int inArray;

    // максимальный и текущий размеры пирамиды
    int maxheapsize;
    int heapsize;

    // восстановление пирамидальной структуры

    void filterDown(int i);
    void filterUp(int i);

public:
    // создание пустой пирамиды
    Heap(int maxsize);
    // преобразование arr в пирамиду
    Heap(T arr[], int n);

    const T& operator[] (int i);

    // возврат значений, связанных с максимальным и текущим размерами пирамиды

    int listSize() const;
    int listEmpty() const;
    int listFull() const;

    // вставка элемента в пирамиду
    void insert(const T& item);

    // удаление корня
    T del();

    // возвращает, присутствует ли данный элемент в пирамиде
    int contains(T element);

    // возвращает индекс элемента или -1, если его нет
    int find_el(T element);
};

// создание пустой пирамиды
template<class T>
Heap<T>::Heap(int maxsize) : maxheapsize(maxsize), heapsize(0), inArray(0), hlist(new T[maxsize])
{}

// преобразование arr в пирамиду. массив перестраивается, а не копируется
template<class T>
Heap<T>::Heap(T *arr, int n) {
    int j, currentpos;

    if (n <= 0)
        throw std::runtime_error("Неправильная размерность массива");

    maxheapsize = n;
    heapsize = n;
    hlist = arr;

    currentpos = (heapsize-2)/2;
    while (currentpos >= 0) {
        filterDown(currentpos);
        currentpos--;
    }
    inArray = 1;
}

// восстановление пирамиды. начиная с индекса i подниматься вверх
// по дереву, переходя от предка к предку. менять элементы местами, если сын меньше родителя
template <class T>
void Heap<T>::filterUp(int i) {
    int currentpos, parentpos;
    T target;

    currentpos = i;
    parentpos = (i - 1) / 2;
    target = hlist[i];

    while (currentpos != 0) {
        if (hlist[parentpos] <= target)
            break;
        else {
            hlist[currentpos] = hlist[parentpos];
            currentpos = parentpos;
            parentpos = (currentpos - 1) / 2;
        }
    }
    hlist[currentpos] = target;
}

// начиная с индекса i меняет местами родителя и сына так, чтобы поддерево,
// начинающееся в узле i, было пирамидой
template <class T>
void Heap<T>::filterDown(int i) {
    int currentpos, childpos;
    T target;

    currentpos = i;
    target = hlist[i];

    childpos = 2 * i + 1;
    while (childpos < heapsize)
    {
        if ((childpos+1 < heapsize) &&
                (hlist[childpos+1] <= hlist[childpos]))
            childpos = childpos + 1;

        if (target <= hlist[childpos])
            break;
        else
        {
            hlist[currentpos] = hlist[childpos];

            currentpos = childpos;
            childpos = 2 * currentpos + 1;
        }
    }
    hlist[currentpos] = target;
}

// вставка элемента в пирамиду
template <class T>
void Heap<T>::insert(const T &item) {
    if (heapsize == maxheapsize)
        throw std::runtime_error("Пирамида заполнена");
    hlist[heapsize] = item;
    filterUp(heapsize);
    heapsize++;
}

// возвращает текущий размер списка
template<class T>
int Heap<T>::listSize() const {
    return heapsize;
}

// возвращает, отсутствуют ли в пирамиде элементы
template<class T>
int Heap<T>::listEmpty() const {
    return heapsize == 0;
}

// возвращает равно ли текущее число элементов максимально возможному
template<class T>
int Heap<T>::listFull() const {
    return heapsize == maxheapsize;
}

template<class T>
const T &Heap<T>::operator[](int i) {
    return hlist[i];
}

// удаление корня
template<class T>
T Heap<T>::del() {
    T tempitem;

    if (heapsize == 0)
        throw std::runtime_error("Пирамида пуста");

    tempitem = hlist[0];
    hlist[0] = hlist[heapsize-1];
    heapsize--;

    filterDown(0);

    return tempitem;
}

template<class T>
int Heap<T>::contains(T element) {
    for (int i=0; i < heapsize; i++)
        if (element == hlist[i])
            return 1;
    return 0;
}

// возвращает индекс элемента или -1, если его нет
template<class T>
int Heap<T>::find_el(T element) {
    for (int i=0; i<heapsize; i++)
        if(element == hlist[i])
            return i;

    return -1;
}

// сортировка массива a размера n по убыванию
template<class T>
void heap_sort(T a[], int n) {
    Heap<T> heap(a, n);
    T el;

    for (int i=n-1; i>=1; i--)
    {
        el = heap.del();
        a[i] = el;
    }
}


#endif //HEAP_HEAP_H

//    Heap(const Heap<T>& H);
//    ~Heap();

//    Heap<T> operator= (const Heap<T>& rhs);
