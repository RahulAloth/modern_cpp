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
using namespace std;


/*
function overloading is same as that of old version of c++
*/
// Function with int parameter
int add(int a, int b) {
    return a + b;
}

// Function with double parameter
double add(double a, double b) {
    return a + b;
}
int function_overloading() {
    cout << "Sum of integers: " << add(5, 3) << endl; // Calls int version
    cout << "Sum of doubles: " << add(5.5, 3.2) << endl; // Calls double version
    return 0;

}

/*
  In C++, the extern "C" keyword is used to tell the C++ compiler to use
  C linkage for the specified function(s). This is particularly useful when 
  you need to call C functions from C++ code or when you want to ensure that your 
  C++ functions can be called from C code
*/

// C++ code
extern "C" {
    void myCFunction(int, int);
}

void myCFunction(int x, int y) {
    cout << "Sum of int's: " << add(x, y) << endl; // Calls double version   
}
