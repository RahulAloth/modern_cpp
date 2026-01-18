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
_______________________________________________________________________________
Feature	              | Raw Pointer	   | Smart Pointer (unique_ptr, shared_ptr) 
_______________________________________________________________________________
Manual memory mgmt	  | ✅ Yes	       | ❌ No (automatic)
RAII compliant	      | ❌ No	       | ✅ Yes
Exception safe	      | ❌ No	       | ✅ Yes
Ownership clarity	  | ❌ No	       | ✅ Yes
________________________________________________________________________________
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
# Pointer Aliasing:
/*
Pointer Aliasing
A foundational concept for optimization, vectorization, and predictable performance
🌱 What is pointer aliasing?
Pointer aliasing happens when two or more pointers refer to the same memory location (or overlapping regions).
*/
void foo(float* a, float* b) {
    *a = *a + 1;
    *b = *a + 2;   // Compiler must assume a and b might alias
}

/*
🧠 How to avoid aliasing penalties
1. Use restrict (C99)

This tells the compiler:
“These pointers never alias. Optimize freely.”

Huge win for NEON vectorization.

*/

void foo(float* __restrict a, float* __restrict b) { 
    *a = *a + 1;
    *b = *a + 2;   // Compiler must assume a and b might alias
}


/*
Avoid passing overlapping pointers
*/
foo(&arr[0], &arr[1]); // Bad: aliasing risk
foo(arrA, arrB); // Good: independent arrays
/*
## Summary (for your notes)

| Concept            | Meaning                               | Performance Impact                       |
|--------------------|----------------------------------------|-----------------------------------------|
| Pointer aliasing   | Two pointers refer to the same memory  | Prevents optimization                   |
| Compiler behavior  | Must assume worst-case aliasing        | No vectorization, no reordering         |
| Avoiding aliasing  | `restrict`, SoA, separate arrays       | Big speedups                            |
| Jetson relevance   | Critical for NEON + CUDA preprocessing | 2×–10× faster loops                     |
*/
