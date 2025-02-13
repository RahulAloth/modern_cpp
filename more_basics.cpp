#include <cstdio>
#include <iostream>

// climits -> defines constants that specify the limits of fundamental integral types 
// for the specific system and compiler implementation used.Likewise cfloat for floating point.
#include <climits>
#include <cfloat>
#include <vector>
#include <assert.h>
#include <map>
#include <initializer_list>
#include <cstdlib>

using namespace std;


/*
function overloading is same as that of old version of c++
*/
// Function with int parameter
int add(int a, int b) {
    return a + b;
}

// Function with double parameter
double add(double a, double b) {
    return a + b;
}
int function_overloading() {
    cout << "Sum of integers: " << add(5, 3) << endl; // Calls int version
    cout << "Sum of doubles: " << add(5.5, 3.2) << endl; // Calls double version
    return 0;

}

/*
  In C++, the extern "C" keyword is used to tell the C++ compiler to use
  C linkage for the specified function(s). This is particularly useful when 
  you need to call C functions from C++ code or when you want to ensure that your 
  C++ functions can be called from C code
*/

// C++ code
extern "C" {
    void myCFunction(int, int);
}

void myCFunction(int x, int y) {
    cout << "Sum of int's: " << add(x, y) << endl; // Calls double version   
}

/*
In Modern C++, default arguments allow you to specify a default value for a 
function parameter. This means that if the caller does not provide a value for 
that parameter, the default value will be used. Here’s a simple example:
*/
void print(int x, int y = 10) {
    std::cout << "x: " << x << ", y: " << y << std::endl;
}

/***********************************************/
/***************************************
Function Pointers: -> are pointers that point to the address of a function, allowing you to call the function indirectly. 
They are useful in various scenarios, such as implementing callback functions, dynamic function calls, and event-driven programming.
*/
// Uage 1: Function pointer as call back functions.
// Callback function
void callbackFunction(int x) {
    std::cout << "Callback function called with value: " << x << std::endl;
}

// Function that accepts a callback
void performOperation(int value, void (*callback)(int)) {
    std::cout << "Performing operation with value: " << value << std::endl;
    // Call the callback function
    callback(value);
}
int main_callback(void) {
    performOperation(10, callbackFunction);
    return 0;
}
/*
Dynamic function call using function pointers:
Usage 2: They allow for dynamic function calls, meaning you can decide at runtime
which function to call. This is particularly useful in scenarios like plugin systems or when implementing a strategy pattern.
*/
// Define some sample functions
void functionA(int x) {
    std::cout << "Function A called with value: " << x << std::endl;
}

void functionB(int x) {
    std::cout << "Function B called with value: " << x << std::endl;
}

void functionC(int x) {
    std::cout << "Function C called with value: " << x << std::endl;
}

// Function to call the appropriate function dynamically
void callFunction(const std::string& funcName, int value, const std::map<std::string, std::function<void(int)>>& funcMap) {
    auto it = funcMap.find(funcName);
    if (it != funcMap.end()) {
        it->second(value); // Call the function
    }
    else {
        std::cout << "Function not found!" << std::endl;
    }
}

int dynamic_function_main() {
    // Create a map of function names to function pointers
    std::map<std::string, std::function<void(int)>> funcMap;
    funcMap["functionA"] = functionA;
    funcMap["functionB"] = functionB;

    // Call functions dynamically
    callFunction("functionA", 10, funcMap);
    callFunction("functionB", 20, funcMap);
    callFunction("functionC", 30, funcMap); // This will print "Function not found!"

    return 0;
}
/*
Function Table:
Function tables, also known as dispatch tables, are often used to map function names or identifiers to 
function pointers, allowing for dynamic function calls.
*/
// Function to call the appropriate function dynamically
void callFunction(const std::string& funcName, const std::map<std::string, void(*)(int)>& funcTable) {
    auto it = funcTable.find(funcName);
    if (it != funcTable.end()) {
        it->second(10); // Call the function
    }
    else {
        std::cout << "Function not found!" << std::endl;
    }
}

int function_table_main() {
    // Create a map of function names to function pointers
    std::map<std::string, void(*)(int)> funcTable;
    funcTable["functionA"] = functionA;
    funcTable["functionB"] = functionB;
    funcTable["functionC"] = functionC;

    // Call functions dynamically
    callFunction("functionA", funcTable);
    callFunction("functionB", funcTable);
    callFunction("functionD", funcTable); // This will print "Function not found!"

    return 0;
}
/*
Function pointer in state machine.
*/
// Define the states
enum State {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
};

// Function prototypes for state handlers
void idleState();
void runningState();
void pausedState();
void stoppedState();

// Map to associate states with their corresponding functions
std::map<State, void(*)()> stateFunctionMap = {
    {STATE_IDLE, idleState},
    {STATE_RUNNING, runningState},
    {STATE_PAUSED, pausedState},
    {STATE_STOPPED, stoppedState}
};

// Current state
State currentState = STATE_IDLE;

// State handler functions
void idleState() {
    std::cout << "System is idle." << std::endl;
    // Transition to running state for demonstration
    currentState = STATE_RUNNING;
}

void runningState() {
    std::cout << "System is running." << std::endl;
    // Transition to paused state for demonstration
    currentState = STATE_PAUSED;
}

void pausedState() {
    std::cout << "System is paused." << std::endl;
    // Transition to stopped state for demonstration
    currentState = STATE_STOPPED;
}

void stoppedState() {
    std::cout << "System is stopped." << std::endl;
    // Transition back to idle state for demonstration
    currentState = STATE_IDLE;
}

int function_state_machine() {
    // Simulate state transitions
    State currentState = STATE_RUNNING;
    stateFunctionMap[currentState](); // This will call runningState()
    return 0;
}

/********************************Name Space : Start ******d*************************************************/
/*In C++, a namespace is a declarative region that provides a scope to the identifiers(names of types, functions,
variables, etc.) inside it.Namespaces are used to organize code into logical groups and to prevent name collisions, 
especially whencode includes multiple libraries. */

namespace names_space{
    int obj_variable;
    void my_function() {
        cout << "Namespace example" << endl;
    };
}
// using alias.
namespace MyAlias = names_space;
// using directive.
using namespace names_space;

using MyAlias::obj_variable;
using names_space::my_function;
/********************************C Style Memory Management : Start   ********************************************************/
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
/********************************C Style Memory Management : End   ********************************************************/
