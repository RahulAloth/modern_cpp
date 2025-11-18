/*
  Introduction:
  In C++, a union is a special data type that allows you to store different
  data types in the same memory location. Only one member can hold a valid
  value at a time. The size of the union equals the size of its largest member.

  Key Characteristics:
  - Memory sharing: All members share the same memory block.
  - Size: Determined by the largest member.
  - Access: Assigning to one member overwrites the previous value.
  - Use case: Store one of several possible types (e.g., variant-like or low-level code).
*/

#include <iostream>

union UnionName {
    int intVal;
    float floatVal;
    char charVal;
};

union Data {
    int i;
    float f;
    char c;
};

int main() {
    Data d;
    d.i = 10;
    std::cout << "Integer: " << d.i << std::endl;

    d.f = 3.14f; // overwrites previous value
    std::cout << "Float: " << d.f << std::endl;

    d.c = 'A'; // overwrites previous value
    std::cout << "Char: " << d.c << std::endl;

    return 0;
}
