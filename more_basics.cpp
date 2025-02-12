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

/**********************************************************************/

