/*
Run-Time Type Information in modern C++.
RTTI (Run-Time Type Information) is a mechanism in C++ that allows you to:
    Discover the dynamic type of an object at runtime.
    Perform safe type conversions in polymorphic hierarchies.
    Query type information for debugging, logging, or conditional logic.
It’s enabled by default in most compilers (though it can be disabled with flags like -fno-rtti in GCC/Clang).

Lets us see an example of using RTTI with the typeid operator.
*/


/*
The typeid operator in modern C++ is used to obtain runtime type information 
(RTTI) about an expression or type. It returns a reference to a std::type_info 
object that describes the type. It’s especially useful in polymorphic hierarchies 
to determine the actual dynamic type of an object at runtime
*/
#include <iostream>
#include <typeinfo>
using namespace std;

class Base { public: virtual ~Base() {} };
class Derived : public Base {};

int main() {
    Base b;
    Derived d;
    Base* ptr = &d;

    cout << typeid(b).name() << endl;    // prints "Base"
    cout << typeid(d).name() << endl;    // prints "Derived"
    cout << typeid(*ptr).name() << endl; // prints "Derived" (runtime check)
}
/*
Modern Best Practices
    Use typeid for debugging, logging, or safe downcasting checks.
    Combine with dynamic_cast for type-safe polymorphic conversions.
    Avoid relying on name() for program logic; use hash_code() or custom type tags if you need stable identifiers.
    In modern designs, prefer polymorphism or templates over explicit type checks.
*/

/*Dynamic Cast Operator
The dynamic_cast operator is part of C++’s Run-Time Type Information (RTTI) system.
It is used to safely convert pointers or references within an inheritance hierarchy,
especially when dealing with polymorphic classes (classes with at least one 
virtual function).
Syntax:
    dynamic_cast<new_type>(expression)
Where new_type is the type you want to cast to, and expression is the pointer or 
reference you want to cast from.
*/

#include <iostream>
#include <typeinfo>
using namespace std;

class Base { public: virtual ~Base() {} };
class Derived : public Base {};
class Other : public Base {};

int main() {
    Base* b = new Derived();

    // Safe downcast
    Derived* d = dynamic_cast<Derived*>(b);
    if (d) cout << "Cast to Derived succeeded\n";

    // Invalid cast
    Other* o = dynamic_cast<Other*>(b);
    if (!o) cout << "Cast to Other failed\n";

    delete b;
}
/*
 type info:
 name() → Returns an implementation-defined string describing the type (compiler-specific).
 hash_code() → Returns a stable hash value for the type.
 Represents information about a type at runtime.
 Returned by the typeid operator.
 Provides methods to query and compare types. 
 */
#include <iostream>
#include <typeinfo>
using namespace std;

class Base { public: virtual ~Base() {} };
class Derived : public Base {};

int main() {
    Base b;
    Derived d;
    Base* ptr = &d;

    // Get type_info objects
    const type_info& ti1 = typeid(b);     // static type: Base
    const type_info& ti2 = typeid(d);     // static type: Derived
    const type_info& ti3 = typeid(*ptr);  // dynamic type: Derived (because Base is polymorphic)

    // Print type names
    cout << "b is: " << ti1.name() << endl;
    cout << "d is: " << ti2.name() << endl;
    cout << "*ptr is: " << ti3.name() << endl;

    // Compare types
    if (ti2 == ti3) {
        cout << "d and *ptr are the same type\n";
    }
}
/*
std::bad_cast
    Defined in the <typeinfo> header.
    It is thrown when a dynamic_cast on a reference type fails.
    Unlike pointer casts (which return nullptr on failure), reference
    casts cannot return “nothing,” so they throw this exception instead.
*/
#include <iostream>
#include <typeinfo>
using namespace std;

class Base { public: virtual ~Base() {} };
class Derived : public Base {};
class Other : public Base {};

int main() {
    Derived d;
    Base& b = d; // reference to Derived object

    try {
        // Valid cast: b actually refers to Derived
        Derived& dRef = dynamic_cast<Derived&>(b);
        cout << "Cast to Derived succeeded\n";

        // Invalid cast: b does not refer to Other
        Other& oRef = dynamic_cast<Other&>(b); // throws std::bad_cast
        cout << "Cast to Other succeeded\n";
    }
    catch (const bad_cast& e) {
        cout << "Caught bad_cast: " << e.what() << endl;
    }
}
