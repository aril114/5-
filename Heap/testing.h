#ifndef HEAP_TESTING_H
#define HEAP_TESTING_H

//               0
//         1           4
//    3        2   8       5
// 9    6   7

Heap<int> createHeap() {
    int heapsize = 10;
    Heap<int> heap(heapsize);

    for (int i=1; i<=heapsize; i++)
        heap.insert(heapsize-i);

    return heap;
}

void contains_test() {
    Heap<int> heap = createHeap();
    int heapsize = heap.listSize();
    for (int i=0; i<heapsize; i++)
        if (!(heap.contains(i)))
            throw std::runtime_error("contains returns false for existing element");

    if(heap.contains(-1))
        throw std::runtime_error("contains returns true for nonexistent element");
}

void find_el_test() {
    Heap<int> heap = createHeap();
    int heapsize = heap.listSize();
    for (int i=0; i<heapsize; i++)
        if (heap.find_el(i) == -1)
            throw std::runtime_error("find_el returns -1 for existing element");

    if(heap.find_el(-1) != -1)
        throw std::runtime_error("find_el returns index of nonexistent element");
}

void insertTest() {
    Heap<int> heap(100);
    int a[100];
    for (int i=100; i>0; i--)
        a[100-i] = i;
    for (int el: a)
        heap.insert(el);

    int node, lchild, rchild;
    for (int i=0; i<100/2-1; i++) {
        node = heap[i];
        lchild = heap[i*2+1];
        rchild = heap[i*2+2];
        if (lchild < node || rchild < node) {
            char buf[50];
            sprintf(buf, "insertTest error.  node: %d. children: %d, %d", i, i*2+1, i*2+2);
            throw std::runtime_error(buf);
        }
    }
}

void testing() {
    insertTest();
    find_el_test();
    contains_test();
}

#endif //HEAP_TESTING_H
