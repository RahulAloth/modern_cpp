/*
Overview

Object slicing occurs when a derived-type object is copied or 
assigned into a base-type object by value. The copy retains only 
the base subobject; any derived members and overrides are lost. 
It commonly happens with assignments, function parameters passed by 
value, return-by-value, and value containers holding a base type.
How slicing happens

    Assignment by value: A derived object is assigned 
    to a base object variable; the base object receives 
    only the base portion.

    Pass-by-value: A function parameter of type Base takes 
    a Derived argument; the function receives a sliced Base copy.

    Return-by-value: A function declared to return Base constructs
     or returns a Derived; callers get a Base slice.

    Containers of base by value: Storing Derived objects in
     std::vector<Base> slices them on insertion; store pointers or polymorphic wrappers instead.
*/
#include <iostream>
#include <string>
using namespace std;

struct Base {
    int id{0};
    virtual string name() const { return "Base"; }
    virtual ~Base() = default;
};

struct Derived : Base {
    string tag{"derived-only"};
    Derived() { id = 42; }
    string name() const override { return "Derived"; }
};
/*
    Effect: b is a standalone Base object. 
    The derived part (tag and the override of name) is 
    gone. Virtual dispatch calls Base::name() b
    ecause the object type is now Base.

Pass-by-value vs. reference/pointer
*/
void take_base_by_value(Base b) { // slicing if passed a Derived
    cout << "By value: " << b.name() << "\n"; // "Base"
}

void take_base_by_ref(const Base& b) { // no slicing
    cout << "By ref: " << b.name() << "\n"; // "Derived" if argument is Derived
}

void take_base_by_ptr(const Base* b) { // no slicing
    cout << "By ptr: " << b->name() << "\n"; // "Derived" if argument is Derived
}

/*
How to prevent slicing
    Prefer references or pointers in interfaces:
        Pass/return by reference or pointer for polymorphic
         types: const Base&, Base*, unique_ptr<Base>, shared_ptr<Base>.
    Use polymorphic containers:
        Store smart pointers: std::vector<std::unique_ptr<Base>>.
        For value semantics across a closed set of types, consider 
        std::variant rather than inheritance.
    Delete or hide copy operations in the base:
        Prevent creating base-by-value copies that invite slicing.
*/

struct Base_corrected {
    Base_corrected() = default;
    Base_corrected(const Base_corrected&) = delete;
    Base_corrected& operator=(const Base_corrected&) = delete;
    virtual ~Base_corrected() = default;
    // ...
};
/*
Or Provide a virtual clone:
    Enable polymorphic copying without slicing by returning a new object of the dynamic type.
*/
struct Base {
    virtual ~Base() = default;
    virtual unique_ptr<Base> clone() const = 0;
};

struct Derived : Base {
    unique_ptr<Base> clone() const override {
        return make_unique<Derived>(*this);
    }
};

int main() {
    Derived d;
    cout << d.name() << " id=" << d.id << " tag=" << d.tag << "\n";

    Base b = d; // SLICING occurs here (copy by value into Base)
    cout << b.name() << " id=" << b.id << "\n"; // prints "Base", tag lost
    take_base_by_value(d);   // slices
    take_base_by_ref(d);     // preserves dynamic type
    take_base_by_ptr(&d);    // preserves dynamic type

    // Usage:
    unique_ptr<Base> copy = some_base_ref.clone(); // retains dynamic type
}

