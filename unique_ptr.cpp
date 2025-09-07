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
