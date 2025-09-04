/*
What is RAII?

RAII is a C++ programming idiom where resource allocation is tied to object lifetime. When an object is created, it acquires a resource (like memory, file handles, etc.), and when it goes out of scope, its destructor releases the resource automatically.

Raw Pointers

Definition: A raw pointer is a basic pointer type (int*, char*, etc.) that directly holds a memory address.

RAII Compatibility: Raw pointers do not follow RAII by themselves. You must manually manage memory using new and delete.

Risks:

Memory leaks (if delete is forgotten)

Dangling pointers (if memory is deleted but pointer is still used)
Exception safety issues

Feature	            | Raw Pointer	   | Smart Pointer (unique_ptr, shared_ptr)
_____________________________________________________________________________
Manual memory mgmt	| ✅ Yes	       | ❌ No (automatic)
RAII compliant	    | ❌ No	         | ✅ Yes
Exception safe	    | ❌ No	         | ✅ Yes
Ownership clarity	  | ❌ No	         | ✅ Yes
______________________________________________________________________________
*/

#include <iostream>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void doSomething() { std::cout << "Using resource\n"; }
};

void rawPointerExample() {
    Resource* res = new Resource();  // Manual allocation
    res->doSomething();
    delete res;                      // Manual deallocation
}

int main_raw() {
    rawPointerExample();             // Call the function here
    return 0;
}
