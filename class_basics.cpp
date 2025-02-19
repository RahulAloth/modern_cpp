/*
This file explains important concepts used in a class. It does not cover very basics of class. It is assume that programmer already having basic understanding of class.
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
/*
COPY CONSTRUCTOR:
A user-defined copy constructor is a constructor that you explicitly define to control how an object is copied.
This is particularly useful when your class involves dynamic memory allocation or other resources that need to be managed carefully. 
By defining your own copy constructor, you can ensure that each object gets its own copy of the resources, preventing issues 
like double deletion or unintended sharing of resources.

Example of a User-Defined Copy Constructor
Here’s an example to illustrate a user-defined copy constructor:
*/

class copy_constructor {
private:
    int* data;

public:
    // Constructor
    copy_constructor(int val) {
        data = new int;
        *data = val;
    }

    // User-defined copy constructor (deep copy)
    copy_constructor(const copy_constructor& source) {
        data = new int;
        *data = *(source.data);
        cout << "User-defined copy constructor called!" << endl;
    }

    // Destructor
    ~copy_constructor() {
        delete data;
    }

    void display() const {
        cout << "Data: " << *data << endl;
    }
};

int main() {
    copy_constructor obj1(10);
    copy_constructor obj2 = obj1; // User-defined copy constructor

    obj1.display();
    obj2.display();

    return 0;
}
/*
Explanation
User-Defined Copy Constructor:
The copy constructor is defined as copy_constructor(const copy_constructor& source). It takes a reference to an object of the same class as a parameter
. In this example, the copy constructor allocates new memory for data and copies the value from the source object’s data to the new memory location. 
This ensures that each object has its own copy of the data, preventing unintended side effects.
When is the Copy Constructor Called?:
The copy constructor is called in the following scenarios:
When an object is initialized from another object of the same type (e.g., Example obj2 = obj1;).
When an object is passed by value to a function.
When an object is returned by value from a function.
*/

