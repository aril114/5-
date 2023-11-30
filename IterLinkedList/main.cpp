#include <iostream>
#include "LinkedList.h"
#include "testing.h"

int main() {
    testing();

    LinkedList<int> ll;
    for (int i=1; i<=10; i++)
        ll.insertRear(i);

    for (int number : ll)
        std::cout << number << "\n";
}
