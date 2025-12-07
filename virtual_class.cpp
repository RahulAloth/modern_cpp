/*
virtual keywords in modern C++—they’re central 
to polymorphism and object-oriented design.

The virtual keyword marks a member function in a base class as one that 
can be overridden in derived classes. It enables runtime polymorphism: 
the correct function is chosen based on the actual object type, not the pointer/reference type.
*/


#include <iostream>
using namespace std;

class Base {
public:
    virtual void speak() { cout << "Base speaking\n"; }
};

class Derived : public Base {
public:
    void speak() override { cout << "Derived speaking\n"; }
};

int main() {
    Base* b = new Derived();
	/*
	Without virtual, this would print 
    "Base speaking" because the call would be resolved at compile time.
	*/
    b->speak(); // Prints "Derived speaking"
}
/*
Modern C++ Enhancements

override (C++11)
    Ensures a derived function actually overrides a base virtual function.
    Prevents subtle bugs from mismatched signatures.
*/

class Derived : public Base {
public:
    void speak() override; // compiler checks correctness
};
/*
    Prevents further overriding of a virtual function.
    Can also be applied to classes to prevent inheritance.
*/
class Derived : public Base {
public:
    void speak() final; // no further overrides allowed
};
/*
 = 0 (Pure Virtual Functions)
    Declares a function as abstract, making the class an abstract base class.
*/
class Interface {
public:
    virtual void run() = 0; // must be implemented in derived class
};
/*
Virtual Destructors
Always mark destructors virtual in polymorphic base classes to ensure proper cleanup.
*/
class Base {
public:
    virtual ~Base() {}
};
/*
Best Practices in Modern C++

Use override consistently—it’s a safety net.
Use final when you want to lock down behavior.
Always declare a virtual destructor in base classes meant for polymorphism.
Prefer interfaces (pure virtual classes) for clean abstraction.
Avoid excessive virtual use in performance-critical paths—consider
alternatives like CRTP (Curiously Recurring Template Pattern).
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() = 0;       // pure virtual
    virtual ~Animal() = default;    // virtual destructor
};

class Dog : public Animal {
public:
    void sound() override { cout << "Woof!\n"; }
};

class GuardDog : public Dog {
public:
    void sound() final override { cout << "Loud Woof!\n"; }
};

int main() {
    Animal* a = new GuardDog();
    a->sound(); // "Loud Woof!"
    delete a;   // safe cleanup
}

