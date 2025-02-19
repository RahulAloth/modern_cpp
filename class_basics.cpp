/*
this Pointer:

The this pointer is an implicit pointer available in non-static member functions of a class. 
It points to the object for which the member function is called.
In the display function, this->value refers to the value member of the current object.

Static Class Member:

A static class member is shared among all objects of the class. It is not tied to any specific object.
In the example, count is a static member that keeps track of the number of Example objects created. It is initialized outside the class definition.

Non-static Data Member Initialization:
Non-static data members are initialized for each object of the class. In the updated example, 
value is initialized using uniform initialization (int value{0};).

Constant Member Functions:

A constant member function is a member function that does not modify any data members of the class. 
It is declared with the const keyword at the end of the function declaration. In the example, display 
is a constant member function, ensuring that it does not modify the object’s state.
*/

#include <iostream>
using namespace std;

class Example {
private:
    int value{0}; // Non-static data member with uniform initialization

public:
    static int count; // Static class member

    // Constructor
    Example(int val) : value{val} {
        count++;
    }

    // Constant member function
    void display() const {
        cout << "Value: " << this->value << endl;
    }

    // Static member function
    static void showCount() {
        cout << "Count: " << count << endl;
    }
};

// Initialize static member
int Example::count = 0;

int class_main() {
    Example obj1(10);
    Example obj2(20);

    obj1.display();
    obj2.display();

    Example::showCount();

    return 0;
}
