/*std::unique_ptr is a smart pointer in C++ that provides exclusive ownership of a dynamically allocated object. It is part of the C++11 standard and is a key tool for writing safe, modern C++ code using the RAII principle.

Key Features of std::unique_ptr

Exclusive ownership: Only one unique_ptr can own a resource at a time.
Automatic deallocation: When the unique_ptr goes out of scope, it automatically deletes the managed object.
Move-only: You cannot copy a unique_ptr, but you can move it using std::move.
Custom deleters: You can specify how the resource should be deleted.
*/

#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void doSomething() { std::cout << "Using resource\n"; }
};



int main() {
    std::unique_ptr<Resource> res = std::make_unique<Resource>();
    res->doSomething();
    // No need to call delete — RAII handles it
    
    // Move Semantics Example
    std::unique_ptr<Resource> res1 = std::make_unique<Resource>();
    std::unique_ptr<Resource> res2 = std::move(res1);  // Transfer ownership

    if (!res1) {
        std::cout << "res1 no longer owns the resource\n";
    }
    std::unique_ptr<int> ptr = std::make_unique<int>(42); // No need to call a delete.
    
    // Only one unique_ptr can own a resource at a time.This makes ownership semantics clear and avoids issues like double deletion.
    std::unique_ptr<int> a = std::make_unique<int>(10);
    std::unique_ptr<int> b = std::move(a); // Ownership transferred
    
    // Works Well with STL Containers
    std::vector<std::unique_ptr<Resource>> resources;
    resources.push_back(std::make_unique<Resource>());
    
    return 0;
}
#include <iostream>
#include <memory>

int main() {
    // Allocate an array of 5 integers on the heap
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);

    // Initialize and print the array
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // No need to manually delete the array
    // It will be automatically deallocated when arr goes out of scope
}

/*Important points to consider:
std::unique_ptr<int[]> is used for arrays (note the []).
std::make_unique<int[]>(size) is the preferred way to allocate.
Automatically deallocates memory when it goes out of scope.
Safer than raw pointers—no risk of forgetting delete[].
Dynamic Memory Allocation: 

*/
#include <iostream>
#include <memory>

int main() {
    // Create a dynamic array of 10 integers
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);

    // Initialize the array
    for (int i = 0; i < 10; ++i) {
        arr[i] = i * 5;
    }

    // Print the array
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // No need to manually delete the array
    // Memory is automatically released when arr goes out of scope
}
// But, Using std::vector is often the best way to manage dynamic arrays in C++ 
// because it handles memory allocation, resizing, and cleanup automatically. 
// It’s safer, more flexible, and more idiomatic than using raw pointers or even smart pointers for arrays.


#include <iostream>
#include <vector>

int main() {
    // Create a dynamic array of 10 integers
    std::vector<int> numbers(10);

    // Initialize the array
    for (int i = 0; i < numbers.size(); ++i) {
        numbers[i] = i * 5;
    }

    // Print the array
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Automatically deallocated when vector goes out of scope
}
/*
Why std::vector is Preferred
________________________________________________________________________________________
Feature	                    | std::vector	    | unique_ptr<int[]>	    | Raw Pointer (int*)
_______________________________________________________________________________________
Automatic memory cleanup	| ✅ Yes	        | ✅ Yes	            | ❌ No
Bounds checking	            | ⚠️ With .at()	    | ❌ No	                | ❌ No
Resizing support	        | ✅ Yes	        | ❌ No	                | ❌ No
Exception safety	        | ✅ High	        | ✅ Medium	            | ❌ Low
STL compatibility	        | ✅ Yes	        | ❌ No	                | ❌ No
*/
