#include <iostream>
#include <vector>
#include <string>
#include <ostream>
using namespace std;

/*
Inheriting constructors : a feature introduced in C++11 and refined in later standard
What Are Inheriting Constructors?
They allow a derived class to reuse the constructors of its base class without 
manually writing forwarding constructors.
Syntax:
*/

class Base {

public:
    Base(int x) { cout << "Base constructed with " << x << endl; }
    Base(double y, int z) {}
};

class Derived : public Base {
public:
    using Base::Base; // Inherit all constructors
};
/*
Key Rules and Behaviors:
Introduced in C++11: using Base::Base; brings all constructors from Base into Derived.
Overloads are preserved: Every constructor in Base becomes available in Derived.
Custom constructors coexist: You can still define your own constructors in Derived.
Default constructor inheritance: If Base has a default constructor, Derived gets it too (unless you define your own).
*/

// Example demonstrating inheriting constructors with Extra Members

class Derived_b : public Base {
    int extra;
public:
    using Base::Base; // inherit constructors

    // Custom constructor for new members
    Derived_b(int x, int y) : Base(x), extra(y) {
        cout << "Derived extra initialized with " << y << endl;
    }
};

int main() {
    Derived d1(10);       // Calls Base(int)
    Derived d2(20, 30);   // Calls custom Derived(int,int)
}
