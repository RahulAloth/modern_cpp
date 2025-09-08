/* 
In C++, weak_ptr is a smart pointer that provides a non-owning reference to an object managed by shared_ptr. It’s used to break circular references and to observe an object without affecting its lifetime.

🔍 Why Use weak_ptr?
Imagine two objects that hold shared_ptrs to each other. This creates a reference cycle, and the reference count never reaches zero—so the memory is never freed. weak_ptr solves this by allowing one of the references to be non-owning.
Key Characteristics
Does not increase the reference count.
Can be used to check if the object still exists.
Must be converted to shared_ptr to access the object.
Useful in observer patterns, caches, and graph structures.
*/

#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> a_ptr; // weak_ptr to avoid circular reference
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a; // weak_ptr avoids increasing reference count

    // Both objects will be destroyed when main ends
}

/*
Without weak_ptr
If b->a_ptr were a shared_ptr, both objects would hold strong references to each other, and neither would be destroyed—causing a memory leak.
Useful Functions
expired(): Checks if the object has been deleted.
lock(): Returns a shared_ptr if the object is still alive.
reset(): Clears the weak_ptr.
✅ Practical Use Case
In GUI frameworks or event systems, listeners often hold weak_ptrs to avoid keeping objects alive unnecessarily.

*/
