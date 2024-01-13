#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <vector>
#include "LinkedList.h"
#include "Node.h"


// хеш-таблица
template <typename T>
class HashTable
{
protected:
    // число блоков; представляет размер таблицы
    unsigned int numBuckets;
    // хеш-таблица есть массив связанных списков
    LinkedList<T> *buckets;
    // хеш-функция и адрес элемента данных,
    //к которому обращались последний раз
    unsigned long (*hf)(T key);
    T *current;
    // количество элементов хеш-таблицы
    unsigned int size; // .,,,
public:
    int get_numBuckets();
    int get_size();
    // конструктор с параметрами, включающими
    // размер таблицы и хеш-функцию
    HashTable(int nbuckets, unsigned long hashf(T key));
    // методы обработки списков
    void insert(const T& key);
    int find(const T& key);
    int del(const T& key);

    // возвращает значение current
    T getCurrent() const;
    ~HashTable();

    // конструктор перемещения
    HashTable<T>(HashTable<T>&& other);
    // конструктор копирования
    HashTable<T>(const HashTable<T>& other);

    // Оператор присваивания перемещением (move assignment)
    HashTable<T> &operator=(HashTable<T>&& other);
    // оператор присваивания копированием
    HashTable<T> &operator=(const HashTable &other);
    };

// Оператор присваивания перемещением (move assignment)
template <typename T>
HashTable<T> &HashTable<T>::operator=(HashTable<T>&& other)
{
    hf = other.hf;
    current = other.current;
    numBuckets = other.numBuckets;
    size = other.size;

    for (int i=0; i<numBuckets; i++) {
        buckets[i] = other.buckets[i];
    }

    other.numBuckets = 0;
    // other.buckets = new LinkedList<T>[0];
    other.buckets = nullptr;
    other.current = nullptr;
    other.hf = nullptr;
    other.size = 0;
    // delete &other;

    return *this;
}


// оператор присваивания копированием
template<typename T>
HashTable<T> &HashTable<T>::operator=(const HashTable &other) {
    if (this == &other)
        return *this;

    delete[] buckets;

    hf = other.hf;
    numBuckets = other.numBuckets;
    buckets = new LinkedList<T>[numBuckets];
    for (int i=0; i<numBuckets; i++)
        buckets[i].copyList(other.buckets[i]);
    current = other.current;
    size = other.size;

    return *this;
}

// конструктор перемещения
template <typename T>
HashTable<T>::HashTable(HashTable<T>&& other)
{
    hf = other.hf;
    numBuckets = other.numBuckets;
    size = other.size;
    current = other.current;

    for (int i=0; i<numBuckets; i++) {
        buckets[i] = other.buckets[i];
    }

    other.numBuckets = 0;
    // other.buckets = new LinkedList<T>[0];
    other.buckets = nullptr;
    other.current = nullptr;
    other.hf = nullptr;
    other.size = 0;
    // delete &other;
}


// конструктор копирования
template <typename T>
HashTable<T>::HashTable(const HashTable<T>& other) {
    hf = other.hf;
//    buckets = new LinkedList<T>();
    numBuckets = other.numBuckets;
    buckets = new LinkedList<T>[numBuckets];
    for (int i=0; i<numBuckets; i++)
        buckets[i].copyList(other.buckets[i]);
    current = other.current;
    size = other.size;
}

// вставка элемента
template <class T>
void HashTable<T>::insert(const T& key)
{
    // hashval — индекс блока (связанного списка)
    int hashval = int(hf(key) % numBuckets);
    // lst — псевдоним для buckets[hashval].
    // помогает обойтись без индексов
    LinkedList<T>& lst = buckets[hashval];
    for (lst.reset() ; !lst.endOfList() ; lst.next())
        // если ключ совпал, обновить данные и выйти
        if (lst.data() == key) {
            lst.data() = key;
            current = &lst.data();
            return;
        }
    // данные, соответствующие этому ключу, не найдены, вставить элемент в список
    lst.insertRear(key);
    Node<T> *rear = lst.getRear();
    current = &(rear->data);
    size++;
}

// Поиск элемента. Возвращает 1, если найдено и 0, если нет
template <class T>
int HashTable<T>::find(const T& key)
{
    // вычислить значение хеш-функции и установить lst
    // на начало соответствующего связанного списка
    int hashval = int(hf(key) % numBuckets);
    LinkedList<T>& lst = buckets[hashval];
    // просматривать узлы связанного списка в поисках key
    for (lst.reset(); !lst.endOfList(); lst.next())
        // если ключ совпал, получить данные, установить current и выйти
        if (lst.data() == key)
        {
            current = &lst.data();
            return 1; // вернуть True
        }
    return 0; // иначе вернуть False
}

// конструктор по количеству цепочек и хеш-функции
template<class T>
HashTable<T>::HashTable(int nbuckets, unsigned long (*hashf)(T)) {
    numBuckets = nbuckets;
    buckets = new LinkedList<T>[nbuckets];
    this->hf = hashf;
    size = 0;
}

// удаление элемента
template<class T>
int HashTable<T>::del(const T &key) {
    // вычислить значение хеш-функции и установить lst
    // на начало соответствующего связанного списка
    int hashval = int(hf(key) % numBuckets);
    LinkedList<T>& lst = buckets[hashval];
    // просматривать узлы связанного списка в поисках key
    for (lst.reset(); !lst.endOfList(); lst.next())
        if (lst.data() == key)
        {
            lst.deleteAt();
            return 1; // вернуть True
        }
    return 0; // иначе вернуть False
}

// возвращает значение current
template<class T>
T HashTable<T>::getCurrent() const {
    return *current;
}

template<typename T>
int HashTable<T>::get_size() {
    return size;
}

template<typename T>
int HashTable<T>::get_numBuckets() {
    return numBuckets;
}

template<typename T>
HashTable<T>::~HashTable() {
//    for (int i=0; i<numBuckets; i++)
    if (buckets != nullptr)
        delete[] buckets;
}

#endif //HASHTABLE_HASHTABLE_H
