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

int play_with_pointers() {
// c++11 introduced a new type of null called nullptr.
// nullptr is type safe and better than old NULL macro.
// So always use nullptr to initalize a pointer, instead of NULL macro,
// & operator is the address of operator.Which tells the address of the variable.
// Definition: A pointer is a variable that holds the memory address of another variable.
// Syntax : Declared using the* operator. For example, int* ptr; declares a pointer to an integer.
// Usage: Pointers can be reassigned to point to different variables.They can also be used for dynamic memory allocation and pointer arithmetic.
// Nullability : Pointers can be null, meaning they can point to no object.
	int variable_x = 10;
	cout << &variable_x << endl << variable_x << endl;
	int* ptr_add = &variable_x;
	cout << ptr_add << endl << *ptr_add << endl;
	return 0;
}
int play_with_references() {
/*
References
	Definition: A reference is an alias for an already existing variable.
	Syntax: Declared using the & operator. For example, int &ref = var; declares a reference to an integer.
	Usage: Once a reference is initialized to a variable, it cannot be changed to refer to another variable. 
	References are often used in function parameters to avoid copying.
	Nullability: References cannot be null; they must always refer to a valid object.
	Reassignment: Pointers can be reassigned, while references cannot.
	Nullability: Pointers can be null, but references cannot.
	Syntax and Usage: Pointers use * and & for declaration and dereferencing, 
	while references use & for declaration and do not require dereferencing
*/
	int var = 10;
	int& ref = var; // ref is an alias for var
	return 0;
}
int const_qualifiers() {
	/*
	The const qualifier in C++ is used to define variables whose values cannot be changed after initialization.
	It can be applied to variables, pointers, function parameters, and member functions. Here are some key points
	about the const qualifier:
	The const qualifier in C++ is used to define variables whose values cannot be changed after initialization.
	It can be applied to variables, pointers, function parameters, and member functions. Here are some key points about the const qualifier:
	** Variable:
	When you declare a variable as const, its value cannot be modified after it is initialized.
	*/
	const int x = 10;
	// x = 20; // Error: x is const
	/*
	** Pointers:
	The const qualifier can be used with pointers in different ways:
	Pointer to const: The value pointed to by the pointer cannot be changed.
	*/

	const int* ptr = &x; // ptr points to a const int
	// *ptr = 20; // Error: cannot modify the value of a const int

	// const Pointer: The pointer itself cannot be changed to point to another address.
	int mx = 100;
	int* const ptr = &mx; // ptr is a const pointer to int
	ptr = &mx; // Error: cannot change the address stored in ptr
	// const Pointer to const: Both the pointer and the value it points to cannot be changed.
	const int* const ptrr = &x; // ptr is a const pointer to a const int
	// *ptrr = 20; // Error: cannot modify the value of a const int
	// ptrr = &y; // Error: cannot change the address stored in ptr
	return 0;
}
/*
Function Parameters
Using const in function parameters can prevent the function from modifying the argument, which is useful for passing large objects efficiently.
*/
void printValue(const int &value) {
	// value cannot be modified
	std::cout << value << std::endl;
}

/* 
Member Functions
When a member function is declared as const, it means that the function does not modify any member variables of the class.
*/

class MyClass {
public:
	int getValue() const {
		return value;
	}
private:
	int value;
};

int main(void){
	play_with_pointers();
	play_with_references();
	return 0;
}
