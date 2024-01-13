#include <iostream>
#include "HashTable.h"
#include "testing.h"

int main() {
    testing();

    HashTable<int> hashTable(100, hf);

    for (int i=0; i<200; i++)
        hashTable.insert(i);

    for (int i=0; i<250; i++) {
            std::cout << i << ": " << (hashTable.find(i) ? "found" : "not found") << " current: " <<
            hashTable.getCurrent() << "\n";
    }
    for (int i=0; i<100; i++)
        if (i % 3 == 0) hashTable.del(i);

    std::cout << "\n\n";

    for (int i=0; i<100; i++) {
        std::cout << i << ": " << (hashTable.find(i) ? "found" : "not found") << " current: " <<
            hashTable.getCurrent() << "\n";
    }
}
