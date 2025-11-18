// ...existing code...
/*
  user_defined_union.cpp

  Short explanation of user-defined unions in modern C++ and small examples.

  Key points (concise):
  - A union is a class type whose non-static data members share the same memory.
  - Only one member (the active member) may hold a valid value at a time.
  - Reading a member that is not the active one is undefined behaviour (except some
    limited cases for standard-layout types with a common initial sequence).
  - For members with non-trivial construction/destruction (e.g., std::string),
    you must manage lifetime manually (placement new and explicit destructor) or
    provide your own constructors/destructor on the union to do that.
  - Prefer std::variant for a type-safe, automatically-managed alternative.
*/

#include <iostream>
#include <string>
#include <new>      // placement new
#include <variant>  // recommended alternative

// Simple POD-style union
union Number {
    int i;
    float f;
    char c;
};

// Union that holds non-trivial member -- lifetimes managed manually
union UValue {
    int tag;           // you typically keep a tag/discriminator
    std::string s;     // non-trivial member

    UValue() : tag(0) {}          // default-initialize tag only
    ~UValue() {}                  // destructor does not automatically destroy s
};

// Safer modern alternative: std::variant
using V = std::variant<int, std::string, float>;

int main() {
    // POD union usage
    Number n;
    n.i = 42; // active member is i
    std::cout << "Number.i = " << n.i << '\n';
    n.f = 3.14f; // now active member is f (overwrites i)
    std::cout << "Number.f = " << n.f << '\n';

    // Using union with non-trivial member: manual construction/destruction
    UValue u;
    u.tag = 1; // indicate string is active
    new (&u.s) std::string("hello union"); // construct std::string inside union storage
    std::cout << "UValue.s = " << u.s << '\n';
    u.s.~basic_string(); // manually destroy active member before reusing union

    // Preferred modern alternative: std::variant (automatic lifetime management)
    V v = 10;
    std::cout << "variant holds int: " << std::get<int>(v) << '\n';
    v = std::string("hello variant");
    std::cout << "variant holds string: " << std::get<std::string>(v) << '\n';

    return 0;
}
// ...existing code...
