#include <memory>
#include <iostream>

int main() {
    // allocate space on the heap for i
    int *i = new int;

    // start a new scope
    {
        // set the memory on the heap to 5
        *i = 5;
        // make up1 point to the space on the heap
        std::unique_ptr<int> up1{i};
        // prints 5
        std::cout << *up1 << "\n";

        // end of the scope of up1, up1 is destroyed
        // destructor frees i, the space on the heap is set to NULL
    }

    // make up1 point to the space on the heap (i has been freed!)
    std::unique_ptr<int> up2{i};
    // prints 0 (since NULL == 0)
    std::cout << *up2 << "\n";

    // allocate space on the heap for j, is placed where i was pointing
    int *j = new int;
    // prints 1 (since i == j)
    std::cout << (i == j) << "\n";
    // set the same location on the heap to 3
    *j = 3;
    // prints 3 (since i == j)
    std::cout << *up2 << "\n";


    return 0;
}
