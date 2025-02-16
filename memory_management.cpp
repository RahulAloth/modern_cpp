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
