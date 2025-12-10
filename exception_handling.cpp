/*
Exception Handling
C++ exception handling is a structured mechanism to detect and manage runtime errors using try,
 throw, and catch blocks, allowing programs to recover gracefully instead of crashing.

What is Exception Handling?
Exception: An unexpected event during program execution (e.g., division by zero, invalid memory access, file I/O failure).
Purpose: Prevents abrupt program termination by transferring control to a handler that can manage the error
🔹 Key Components
try block
Contains code that may cause an exception.
throw statement
Signals an error by "throwing" an exception object.
catch block
Handles the exception thrown in the try block.
*/
#include <iostream>
using namespace std;

int main() {
    try {
        int x = 10, y = 0;
        if (y == 0) throw runtime_error("Division by zero!");
        cout << x / y;
    }
    catch (runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
/*
In C++, you can attach multiple catch blocks to a single try block to handle different 
types of exceptions separately. This allows you to write more precise error-handling 
code depending on the type of exception thrown
 
How Multiple Catch Blocks Work
    A try block can be followed by several catch blocks.
    When an exception is thrown, the runtime searches for the first matching catch block (based on type).
    Only one matching catch block executes; others are ignored.
    If no match is found, the exception propagates further (stack unwinding).
*/

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        int a = 10, b = 0;
        if (b == 0) throw runtime_error("Division by zero!");
        cout << a / b;
    }
    catch (runtime_error& e) {   // handles runtime errors
        cout << "Runtime error: " << e.what() << endl;
    }
    catch (logic_error& e) {     // handles logic errors
        cout << "Logic error: " << e.what() << endl;
    }
    catch (...) {                // catch-all handler
        cout << "Unknown exception caught!" << endl;
    }
    return 0;
}
/*
Stack unwinding in C++ is the process of cleaning up the 
function call stack when an exception is thrown and not immediately
 handled. It ensures that local objects are destroyed in reverse order
  of construction as control moves back through the call chain to find
   a matching catch block
Summary: Stack unwinding in C++ is the automatic cleanup of 
local objects when an exception propagates up the call stack.
 It guarantees resource safety but requires careful design of
  destructors and exception handling.
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class Demo {
public:
    Demo(const string& name) : name(name) {
        cout << "Constructing " << name << endl;
    }
    ~Demo() {
        cout << "Destructing " << name << endl;
    }
private:
    string name;
};

void func2() {
    Demo d2("d2");
    throw runtime_error("Error in func2");
}

void func1() {
    Demo d1("d1");
    func2();
}

int main() {
    try {
        func1();
    }
    catch (runtime_error& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
}

