#include <cstdlib>

/*
Memory Management:
C/C++ Programs are provided with different types of memory areas.
* Stack -> Allocated automatically for local variable.
* data section -> allocated for global and static data.
* heap -> allocated at runtime.
* All memory is taken from the process address space.
* C/C++ programms support for memory allocation at run-time(dynamic).
* Allocation on the heap has to be managed by the programmer.
* Stack and data section allocations are managed by the runtime.

Dynamic Momeory Allocation in C.
* malloc : allocate raw memory on the heap.
* calloc : allocate memory on the heap and initializes it to zero.
* realloc : allocates larger chunk of memory for an existing allocation.
* free : deallocates / releases the momory allocated through the above functions.
*malloc:
	The malloc is used to allocate a block of memory dynamically.
	It comes from the C standard library and is included via the <cstdlib> header.
	void* malloc(size_t size); -> size: The number of bytes to allocate.
	On success, malloc returns a pointer to the allocated memory block.
	If the allocation fails, it returns NULL.
*/
int memory_management_malloc() {
    int* ptr;
    int n = 5;

    // Allocate memory for 5 integers
    ptr = (int*)malloc(n * sizeof(int));

    // Check if memory has been allocated successfully
    if (ptr == NULL) {
        std::cout << "Memory allocation failed\n";
        return 1;
    }

    // Initialize and print the allocated memory
    for (int i = 0; i < n; ++i) {
        ptr[i] = i + 1;
        std::cout << ptr[i] << " ";
    }

    // Free the allocated memory
    free(ptr);
	return 0;
}

/*
The calloc used to allocate memory for an array of elements and initialize all bytes to zero.
It is part of the C standard library and can be included via the <cstdlib> header.

Function: void* calloc(size_t num, size_t size);
* num: The number of elements to allocate.
* size: The size of each element in bytes
* On success, calloc returns a pointer to the allocated memory block.Else it returns NULL.
* Zero Initialization: Unlike malloc, calloc initializes the allocated memory to zero.
* Casting: The void* returned by calloc needs to be cast to the appropriate pointer type.
* Freeing Memory: Always use free to deallocate the memory allocated by calloc to avoid memory leaks.
*/
int memory_management_calloc() {
    int* ptr;
    int n = 5;
    // Allocate memory for an array of 5 integers
    ptr = (int*)calloc(n, sizeof(int));

    // Check if memory has been allocated successfully
    if (ptr == NULL) {
        std::cout << "Memory allocation failed\n";
        return 1;
    }

    // Print the initialized memory (all zeros)
    for (int i = 0; i < n; ++i) {
        std::cout << ptr[i] << " ";
    }

    // Free the allocated memory
    free(ptr);
}

/*
The realloc function in is used to resize a previously allocated memory block.
It is part of the C standard library and can be included via the <cstdlib> header.
Function: void* realloc(void* ptr, size_t new_size);
* Parameters
    * ptr: A pointer to the memory block to be reallocated. This block must have been 
           previously allocated by malloc, calloc, or realloc.
    * new_size: The new size for the memory block in bytes.
* Return Value
On success, realloc returns a pointer to the reallocated memory block, which may be the same as ptr or a new location. Else return NULL.
*/
int memory_management_realloc() {
    int* ptr;
    int n = 5;

    // Allocate memory for 5 integers
    ptr = (int*)malloc(n * sizeof(int));

    // Check if memory has been allocated successfully
    if (ptr == NULL) {
        std::cout << "Memory allocation failed\n";
        return 1;
    }

    // Initialize the allocated memory
    for (int i = 0; i < n; ++i) {
        ptr[i] = i + 1;
    }

    // Reallocate memory for 10 integers
    ptr = (int*)realloc(ptr, 10 * sizeof(int));

    // Check if memory has been reallocated successfully
    if (ptr == NULL) {
        std::cout << "Memory reallocation failed\n";
        return 1;
    }

    // Initialize the newly allocated memory
    for (int i = 5; i < 10; ++i) {
        ptr[i] = i + 1;
    }

    // Print the reallocated memory
    for (int i = 0; i < 10; ++i) {
        std::cout << ptr[i] << " ";
    }

    // Free the allocated memory
    free(ptr);
}

/*
Dynamic memory allocation in c++
new: Allocates memory on heap.
delete : deallocate memory.
Compile-Time Allocation: Memory is allocated at compile time.
Fixed Size: The size of the memory block is fixed and cannot be changed during runtime.
Run-Time Allocation: Memory is allocated during the execution of the program.
Flexible Size: The size of the memory block can be changed during runtime.
*/

int dynamic_memory_allocation_new() {
    // Allocate memory for a single integer
    int* ptr = new int;
    *ptr = 5;
    std::cout << "Value: " << *ptr << std::endl;

    // Allocate memory for an array of 10 integers
    int* arr = new int[10];
    for (int i = 0; i < 10; ++i) {
        arr[i] = i + 1;
    }

    // Print the array
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Deallocate memory and set pointers to nullptr
    delete ptr;
    ptr = nullptr; // Set pointer to nullptr

    // Deallocate memory and set pointers to nullptr
    delete[] arr;
    arr = nullptr; // Set pointer to nullpt

    return 0;
}
/*
Effective memory management is crucial for writing robust, efficient, and leak-free applications, especially in languages like C++ that give you
direct control over memory. Here are some best practices for memory management:
🔹 1. Use Smart Pointers
Prefer smart pointers over raw pointers:

std::unique_ptr: for sole ownership.
std::shared_ptr: for shared ownership.
std::weak_ptr: to break circular references in shared ownership.
These automatically manage memory and reduce the risk of leaks.
🔹 2. Avoid Manual new and delete
Use smart pointers or container classes (like std::vector, std::string) instead of manually allocating and deallocating memory.
🔹 3. Break Circular References
As discussed earlier, use std::weak_ptr to break cycles in std::shared_ptr graphs.
🔹 4. RAII (Resource Acquisition Is Initialization)
Encapsulate resource management in objects whose lifetimes are tied to scope:
RAII (Resource Acquisition Is Initialization) is a fundamental C++ programming idiom that ensures resource safety by tying the lifetime of 
a resource (like memory, file handles, sockets, etc.) to the lifetime of an object.

🔑 Key Idea:
When an object is created, it acquires a resource in its constructor, and when the object goes out of scope, its destructor 
releases the resource automatically.
Prevents resource leaks
Simplifies exception safety
Makes code cleaner and more maintainable
*/

#include <iostream>
class ScopedArray {
private:
    int* data;
    size_t size;

public:
    // Constructor acquires the resource
    ScopedArray(size_t n) : size(n) {
        data = new int[n];
        std::cout << "Allocated array of size " << size << "\n";
    }

    // Destructor releases the resource
    ~ScopedArray() {
        delete[] data;
        std::cout << "Deallocated array\n";
    }

    // Accessor
    int& operator[](size_t indexrn data[index];
    }

    // Prevent copying (to avoid double deletion)
    ScopedArray(const ScopedArray&) = delete;
    ScopedArray& operator=(const ScopedArray&) = delete;

    // Allow move semantics
    ScopedArray(ScopedArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    ScopedArray& operator=(ScopedArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
int main() {
    ScopedArray arr(5);
    for (size_t i = 0; i < 5; ++i) {
        arr[i] = static_cast<int>(i * 10);
    }

    for (size_t i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // No need to manually delete the array
    // Destructor will be called automatically
}

/*
Constructor acquires the resource (new int[n])
Destructor releases it (delete[])
Copying is disabled to prevent accidental double deletion
Move semantics are supported for safe transfers
Would you like a RAII example for something more advanced, like file handles, mutex locks, or sockets?

C++
std::ifstream file("data.txt"); // Automatically closes when out of scope
🔹 5. Use Containers Wisely
Standard containers like std::vector, std::map, and std::list manage memory internally and are safer than raw arrays or manual memory management.
🔹 6. Avoid Memory Leaks
Use tools like:
Valgrind (Linux)
Visual Studio Diagnostics Tools
AddressSanitizer
These help detect leaks and invalid memory access.
🔹 7. Minimize Heap Allocations
Prefer stack allocation when possible. Heap allocations are slower and more error-prone.
*/

// Heap allocation.
#include <iostream>

void heapExample() {
    int* numbers = new int[5]; // Allocated on the heap

    for (int i = 0; i < 5; ++i) {
        numbers[i] = i * 10;
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";

    delete[] numbers; // Must manually deallocate
}
// Stack Allocation.
#include <iostream>

void stackExample() {
    int numbers[5]; // Allocated on the stack

    for (int i = 0; i < 5; ++i) {
        numbers[i] = i * 10;
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";

    // Automatically deallocated when function ends
}
/*
🔹 8. Be Mindful of Object Lifetimes
Ensure that objects are not accessed after they are destroyed. This is especially important when using raw pointers or references.
🔹 9. Use Move Semantics
Use std::move to transfer ownership efficiently and avoid unnecessary copies.
🔹 10. Initialize All Variables
Uninitialized memory can lead to undefined behavior. Always initialize variables, especially pointers.
*/
