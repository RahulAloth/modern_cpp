/*
In C++, a deleter is a callable object (like a function, lambda, or functor) that defines how to destroy or deallocate a resource—typically used with smart pointers like std::unique_ptr or std::shared_ptr.

Why is a deleter useful?
Sometimes, the default deletion behavior (delete or delete[]) isn't appropriate. For example:

You might be managing a resource that needs a custom cleanup function (like a file handle or a socket).
You might be using a custom memory allocator.
You might need to delete an array instead of a single object.
*/

#include <iostream>
#include <memory>

void customDeleter(int* ptr) {
    std::cout << "Custom deleting int: " << *ptr << std::endl;
    delete ptr;
}

int main() {
    std::unique_ptr<int, decltype(&customDeleter)> ptr(new int(42), &customDeleter);
    // When ptr goes out of scope, customDeleter is called
}
/*
Key Points:
std::unique_ptr and std::shared_ptr can take a custom deleter as a second template argument.
The deleter is called automatically when the smart pointer is destroyed.
This is especially useful for managing non-memory resources or using custom deletion logic.
*/
// Another example with shared pointer.

#include <iostream>
#include <memory>
#include <cstdio> // for FILE, fopen, fclose

int main() {
    // Custom deleter for FILE*
    auto fileDeleter =  {
        if (file) {
            std::cout << "Closing file..." << std::endl;
            fclose(file);
        }
    };

    // Create shared_ptr with custom deleter
    std::shared_ptr<FILE> filePtr(fopen("example.txt", "w"), fileDeleter);

    if (filePtr) {
        std::cout << "Writing to file..." << std::endl;
        fprintf(filePtr.get(), "Hello from shared_ptr with custom deleter!\n");
    }

    // filePtr goes out of scope here, and fileDeleter is called automatically
}

