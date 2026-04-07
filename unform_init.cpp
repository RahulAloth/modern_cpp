#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <climits>
#include <cfloat>
#include <initializer_list>

/*
    -------------------------------------------------------------------------
    The “Most Vexing Parse”
    -------------------------------------------------------------------------
    Coined by Scott Meyers, this refers to a syntactic ambiguity in C++ where
    a statement intended to create an object is instead interpreted by the
    compiler as a *function declaration*.

    Example:

        Widget w(Widget());   // This declares a function, not an object.

    Uniform initialization {} solves this problem:

        Widget w{Widget{}};   // Always an object, never a function declaration.
    -------------------------------------------------------------------------
*/

/*
    -------------------------------------------------------------------------
    What is C++?
    -------------------------------------------------------------------------
    • General-purpose programming language
    • Supports object-oriented, imperative, and generic programming
    • Designed for system programming and performance-critical applications
    • Low-level control like C, but with rich abstractions

    Modern C++ (C++11 and beyond):
    • Move semantics
    • Smart pointers
    • Automatic type inference (auto)
    • Threading support
    • Lambdas
    • Uniform initialization
    • constexpr and compile-time programming

    ISO Standard Committee:
    • First standard: C++98
    • Minor revision: C++03
    • Major revision: C++11
    • Enhancements: C++14, C++17, C++20, C++23

    -------------------------------------------------------------------------
    C++ Build Steps
    -------------------------------------------------------------------------
    1. Preprocessing
       - Handles #include, #define, macros

    2. Compilation
       - Syntax checking
       - Converts code to object files (.o or .obj)

    3. Linking
       - Links object files with libraries
       - Produces final executable

    -------------------------------------------------------------------------
    Primitive Types
    -------------------------------------------------------------------------
    Arithmetic types:
        • Integral: bool, char, wchar_t, char16_t, char32_t, short, int, long
        • Floating point: float, double, long double

    Void:
        • Used for pointers and functions

    Modifiers:
        • signed, unsigned, short, long

    Qualifiers:
        • const, volatile, mutable

    Always initialize variables to avoid undefined behavior.
    -------------------------------------------------------------------------
*/

/*
    Uniform initialization in C++ is a feature introduced in C++11 to provide a
    consistent and unambiguous syntax for initializing variables and objects.
    It uses curly braces {} to initialize variables, arrays, and objects,
    helping avoid many pitfalls of older initialization methods.

    Key points:
    - Consistent syntax for all types
    - Prevents narrowing conversions
    - Works with std::initializer_list
    - Avoids the “most vexing parse”
*/

void uniform_initialization() {

    /**************************************************************************
     * 1. Consistent Syntax
     **************************************************************************/

    int x{5};
    double arr[]{1, 2, 3, 4, 5};
    std::vector<int> vec{1, 2, 3};

    /**************************************************************************
     * 2. Avoid Narrowing Conversions
     **************************************************************************/

    // int xy{3.14};  // ERROR: narrowing conversion

    /**************************************************************************
     * 3. Initialization of Structs (even without constructors)
     **************************************************************************/

    struct Pointx {
        int x;
        int y;
    };

    Pointx p{10, 20};

    /**************************************************************************
     * 4. Initialization Lists
     **************************************************************************/

    std::vector<int> vec_sample{1, 2, 3, 4, 5};

    /**************************************************************************
     * 5. Avoid older initialization styles
     **************************************************************************/

    int a1;                 // Uninitialized
    int a2 = 0;             // Copy initialization
    int a3(8);              // Direct initialization
    char d3[8] = {'a','b','c','d'}; // Aggregate initialization
    int B1{};               // Value initialization (zero-initialized)

    /**************************************************************************
     * 6. More Uniform Initialization Examples
     **************************************************************************/

    // Primitive types
    int xa{5};
    double y{3.14};
    char c{'A'};

    // Arrays
    int arr_int[]{1, 2, 3, 4, 5};
    double values[]{2.5, 3.5, 4.5};

    // STL containers
    std::vector<int> vec_test{1, 2, 3, 4, 5};
    std::map<int, std::string> myMap{
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // User-defined types
    struct Point {
        int x;
        int y;
    };

    Point px{10, 20};

    class Rectangle {
    public:
        int width;
        int height;
    };

    Rectangle rect{30, 40};

    // std::initializer_list example
    class MyClass {
    public:
        MyClass(std::initializer_list<int> list) {
            for (auto elem : list) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    };

    MyClass obj{1, 2, 3, 4, 5};

    // Nested initialization
    struct Inner {
        int a;
        double b;
    };

    struct Outer {
        Inner inner;
        std::string name;
    };

    Outer outer{{1, 2.5}, "example"};
}

/*
    main() — Entry point
    Demonstrates uniform initialization examples.
*/

int main() {

    using namespace std;

    cout << "=== Primitive Types Example ===\n";

    int age{25};        // uniform initialization
    char buff[512]{};   // zero-initialized buffer

    cout << "Age: " << age << "\n";

    cout << "Enter a name: ";
    cin.getline(buff, 64);

    cout << "Name: " << buff << "\n";

    std::cout << "Demonstrating Uniform Initialization in C++11 and beyond:\n\n";
    uniform_initialization();
    // STL containers
    std::vector<int> vec_ex{1, 2, 3, 4, 5};
    std::map<int, std::string> myMapEx{
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    std::cout << vec_ex.back(); // Get last element
    vec_ex.pop_back(); // Remove last element
    std::cout << vec_ex.back(); // Get last element
    vec_ex.push_back(6); // Add new element
    std::cout << vec_ex.back(); // Get last element


    for (const auto& elem : vec_ex) {
        std::cout << elem << " ";
    }
    std::cout << "\nMap contents:\n";
    for (const auto& pair : myMapEx) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    myMapEx[4] = "four"; // Add new key-value pair
    std::cout << "After adding new pair:\n";
    for (const auto& pair : myMapEx) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    return 0;
}
