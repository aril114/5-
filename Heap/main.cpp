#include <iostream>
#include "Heap.h"
#include "testing.h"
int main() {
//    Heap<int> heap(100);
//    int a[100];
//    for (int i=100; i>0; i--)
//        a[100-i] = i;
//    for (int el: a)
//        heap.insert(el);

//    for (int i=0; i<100; i++)
//        std::cout << heap[i] << "\n";

    int a[100];

    heap_sort(a, 100);

    for(int el: a)
        std::cout << el << "\n";

    testing();
}
