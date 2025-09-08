/*
A shared_ptr is a smart pointer in C++ that manages the lifetime of a dynamically allocated object through reference counting. It is part of the C++ Standard Library (<memory> header) and is used to ensure that an object is automatically deleted when it is no longer needed—specifically, when the last shared_ptr pointing to it is destroyed or reset.


1. Reference Counting
Each shared_ptr maintains a reference count (internally via a control block). When a new shared_ptr is created from another, the count increases. When a shared_ptr is destroyed or reset, the count decreases. When the count reaches zero, the managed object is deleted.
 
2. Shared Ownership
Multiple shared_ptr instances can own the same object. This is useful when ownership is not exclusive, such as in graph structures or observer patterns.

3. Automatic Memory Management
When the last shared_ptr goes out of scope, the object is automatically deleted—preventing memory leaks

*/

#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "Constructor\n"; }
    ~MyClass() { std::cout << "Destructor\n"; }
    void greet() { std::cout << "Hello from MyClass\n"; }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    {
        std::shared_ptr<MyClass> ptr2 = ptr1; // shared ownership
        ptr2->greet();
        std::cout << "Use count: " << ptr1.use_count() << "\n"; // 2
    } // ptr2 goes out of scope

    std::cout << "Use count after ptr2 is gone: " << ptr1.use_count() << "\n"; // 1
} // ptr1 goes out of scope, object is destroyed

/*
Important Functions
std::make_shared<T>(): Preferred way to create a shared_ptr. It’s more efficient and safer.
use_count(): Returns the number of shared_ptr instances managing the object.
get(): Returns the raw pointer.
reset(): Releases ownership and optionally takes a new pointer.
unique(): Returns true if the shared_ptr is the only one managing the object.

Common Pitfalls
Circular References: If two objects hold shared_ptrs to each other, they will never be destroyed. Use weak_ptr to break the cycle.
Overhead: Slightly more memory and performance overhead due to reference counting.
Not Thread-Safe for Object Access: While reference counting is thread-safe, access to the object itself is not.
*/



