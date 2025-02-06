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

/*
What is C++
•	General purpose programming language
•	Object oriented, imperative, generic
•	Emphasis on system programming
•	Low-level like C, but feature rich.
•	c++ build steps
Modern C++:
•	Encompasses features of C++11
•	Move semantics
•	Smart pointers
•	Automatic type inference
•	Threading
•	Lambda
ISO Standard committee:
•	Published first standard in 1998, followed by a minor revision in 2003
•	Major change in 2011, with lots of new features
•	2014 added a minor change, mostly enhancements.
C++ Build Steps
•	Preprocessing
    o	Statement beginning with # are expanded or replaced
    o	Macros are expanded
    •	Compilation
    o	Code is checked for correct syntax
    o	Converted into object code
•	Linking
    o	The Object code is linked with the standard libraries
•	The output of the linking is the executable file.
Primitive Types
•	Arithmetic & void
•	Arithmetic-> Integral & floating point
•	Integral types -> bool, char, wchar_t,char16_t,char32_t,short,int,long.
•	Floating point -> float & double
•	Void is a special type used with pointers & functions.
*/

// Declaration or Prototype of the function.
int add(int x, int y);


// In c++, main return void is a non-standard.
int main(void){
    using namespace std;
/*
Primitive Types:
•	Arithmetic and void.
•	Arithmetic -> Integral & floating point
•	Integral type > bool, char, wchar_t,char16_t,char32_t,short, int, long
•	Floating point-> float & double
•	Void is a special type used with pointers & functions.
Modifiers:
•	Modifiers are the keywords used to alter the properties of fundamental data types, making them
    more suitable for specific needs. (Signed, unsigned, short, long).
•	All types can be qualified with qualifiers. Qualifiers are keywords that specify additional properties 
    for variables, affecting how they can be accessed or modified( const, volatile, mutable). 
    In C++, the mutable keyword allows a member of an object to be modified even if the object is declared as const.
•	All types occupy memory and can hold a range of values.
•	Memory requirements may change with platform.
•	Better to initlaize the variables during declaration to avoid bugs.
Examples are below:
*/
    int age = 25;
    char buff[512];
    std::cout << "Age: " << age << std::endl;
    cout << "Enter a name ";
    cin.getline(buff, 64, '\n');
    cout << "Name " << buff << endl;
    int result = add(5, 5);
	return 0;
}

int add(int x, int y) {
    int sum = x + y;
    return sum;
}

/*Uniform initialization in C++ is a feature introduced in C++11 to provide a
consistent and unambiguous syntax for initializing variables and objects.
It uses curly braces{} to initialize variables, arrays, and objects,
which helps avoid some of the pitfalls of older initialization methods.
Key points are discussed below:*/
void uniform_initialization() {
    // consistent Syntax: Use curly bracket, whether its primitive type, array or an object.
    int x{ 5 }; // init integer
    double arr[]{ 1,2,3,4,5 }; // init array
    std::vector<int> vec{ 1,2,3 }; // init vector
    // avoid norrowing conversions: UI prevents narrowing conversions, which leads data loss.
    // int xy{ 3.14 }; // This leads to an Error: narrowing conversion from double to int (conversion from 'double'
                    //to 'int' requires a narrowing conversion)
    // Initialization of Classes and Structs: You can use uniform initialization to initialize classes and structs,
    // even if they don’t have a constructor.
    struct Pointx {
        int x;
        int y;
    };
    Pointx p{ 10, 20 }; // Initializes a Point object
    // Initialization Lists : It can be used with std::initializer_list to initialize containers and other objects.
    std::vector<int> vec_sample = { 1, 2, 3, 4, 5 };

    // The “most vexing parse” is a term coined by Scott Meyers to describe a specific form of syntactic ambiguity 
    // in C++ where the compiler interprets a statement as a function declaration rather than an object or variable 
    // initialization.This can lead to confusing and unexpected behavior.
    // Example initalize as int Obj();

    // Avoid following:
    int a1; // uninitialized.
    int a2 = 0; // Copy initialization.
    int a3(8); // Direct initalization
    char d3[8] = { 'a','b','c','d', }; // Aggregate initialization-
    int B1{}; // Value initalization.
    /*
    Uniform initlaition forces the initlization, we can use direct initlization on arrays, it prevents narrow initialization.
    We have a uniform syntax for the variables.
    */


    /************************************************************************************/
    /*                      Uniform initalization examples                              */
    /************************************************************************************/
    //Initializing Primitive Types
    int xa{ 5 }; // Initializes an integer
    double y{ 3.14 }; // Initializes a double
    char c{ 'A' }; // Initializes a char
    // Initializing Arrays
    int arr_int[]{ 1, 2, 3, 4, 5 }; // Initializes an array of integers
    double values[]{ 2.5, 3.5, 4.5 }; // Initializes an array of doubles
    // Initializing Standard Library Containers
    std::vector<int> vec_test{ 1, 2, 3, 4, 5 }; // Initializes a vector with values
    std::map<int, std::string> myMap{ {1, "one"}, {2, "two"}, {3, "three"} }; // Initializes a map with key-value pairs
    // Initializing User-Defined Types (Structs and Classes)
    struct Point {
        int x;
        int y;
    };

    Point px{ 10, 20 }; // Initializes a Point object

    class Rectangle {
    public:
        int width;
        int height;
    };

    Rectangle rect{ 30, 40 }; // Initializes a Rectangle object
    // Initializing with std::initializer_list
    class MyClass {
    public:
        MyClass(std::initializer_list<int> list) {
            for (auto elem : list) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    };

    MyClass obj{ 1, 2, 3, 4, 5 }; // Initializes MyClass with an initializer list
    // Initializing Nested Structures
    struct Inner {
        int a;
        double b;
    };

    struct Outer {
        Inner inner;
        std::string name;
    };
    Outer outer{ {1, 2.5}, "example" }; // Initializes an Outer object with nested Inner object
}
