#ifndef HASHTABLE_TESTING_H
#define HASHTABLE_TESTING_H

#include <stdexcept>

const unsigned int HT_NUMBUCKETS = 250;
const unsigned int HT_SIZE = 50;

unsigned long hf(int key)
{
    return key;
}

// возвращает хеш-таблицу с количеством блоков HT_NUMBUCKETS
// и элементами со значениями [0:HT_SIZE)
HashTable<int> create_hashtable() {
    HashTable<int> hashTable(HT_NUMBUCKETS, hf);
    for (int i=0; i<HT_SIZE; i++)
        hashTable.insert(i);
    return hashTable;
}

// проверка вставка и поиска
void insert_find_test() {
    HashTable<int> hashTable(HT_NUMBUCKETS, hf);
    for(int i=0; i<HT_SIZE; i++)
        hashTable.insert(i);
    for(int i=0; i<HT_SIZE; i++)
        if (!hashTable.find(i)) throw std::runtime_error("couldn't find inserted element");
    for (int i=0; i<HT_SIZE; i++)
        if (hashTable.find(HT_SIZE+i)) throw std::runtime_error("found not inserted element");
}

// проверка конструкторов копирования и перемещения
void constructors_test() {
    HashTable<int> hashTable = create_hashtable();
    HashTable<int> copied_HashTable = HashTable<int>(hashTable);
    for (int i = 0; i<HT_SIZE; i++) {
        if (!hashTable.find(i) || !copied_HashTable.find(i)) {
            throw std::runtime_error("Копирующий конструктор: не удалось найти элемент, который должен был быть "
                                     "и в исходной, и в скопированной хеш-таблице.");
        }
    }

    HashTable<int> moved_hashTable = HashTable<int>(std::move(hashTable));
    for (int i = 0; i<HT_SIZE; i++) {
        if (!moved_hashTable.find(i)) {
            throw std::runtime_error("Конструктор перемещения: в перемещенном объекте не найден элемент.");
        }
    }
}

void testing() {
    insert_find_test();
    constructors_test();
}

#endif //HASHTABLE_TESTING_H
