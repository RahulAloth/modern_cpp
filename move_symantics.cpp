L-Value                                             |      R-Value
.............................................................................................................
L-Value has a name	                            |      R-Value does not have a name
All variables are l-values	                    |      R-Value is a temporary value
Can be assigned values	                            |      R-Value cannot be assigned values
Some expressions return l-values	            |      Some expressions return r-values
L-Value persists beyond the expression	            |      R-Value does not persist beyond the expression
Functions that return by reference return l-values  |      Functions that return by value return r-values
Reference to l-value (called l-value reference)	    |      Reference to r-value (called r-value reference)
.............................................................................................................
/*
The std::move function in C++11 is a utility that facilitates move semantics, allowing efficient transfer of resources from one object to another.
What is std::move?
std::move is a function that casts an object to an rvalue reference, indicating that the object can be "moved from". This means the resources held
by the object can be transferred to another object without copying.

How does it work?
When you use std::move, it converts an lvalue (like a named variable) into an xvalue, which tells the compiler that the object can be 
"plundered". Essentially, it allows the compiler to transfer the object's resources to another object, which is more efficient than copying.

When should it be used?
std::move is typically used in scenarios where you want to transfer ownership of resources, such as in constructors, assignment operators, 
and functions that return objects1. For example, it can be used to swap two objects without making unnecessary copies.

Efficiency: std::move helps avoid unnecessary copying, making operations faster and more memory-efficient.
Safety: After an object is moved, it should not be used in a way that assumes it still owns its resources.

*/
#include <iostream>
#include <utility> // for std::move
#include <vector>

//Returns r-value
int addition(int x, int y) {
	return x + y;
}

//Return l-value
int & square_function(int &x) {
	x *= x;
	return x;
}

void print(int &x) {
	std::cout << "Print(int&)" << std::endl; 
}
void print(const int &x) {
	std::cout << "Print(const int&)" << std::endl;

}

class MyClass {
public:
    std::vector<int> data;

    // Constructor
    MyClass(std::vector<int> d) : data(std::move(d)) {}

    // Move constructor
    MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {}

    // Move assignment operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }
};


int main() {

	//x is lvalue
	int x = 10;
	
	//ref is l-value reference
	int &ref = x ;

	//square_function returns an l-value
	int &ref2 = square_function(x) ;
  
	//Binds to function that accepts l-value reference
	print(x);
	

	//rv is r-value reference
	int &&rv = 8 ;
	
	//Add returns a temporary (r-value)
	int &&rv2 = addition(3,5) ;
	//Binds to function that accepts a temporary, i.e. r-value reference
	print(5);


	// class Example:
    std::vector<int> vec = {1, 2, 3, 4, 5};
    MyClass obj1(vec); // Move vec into obj1
    MyClass obj2(std::move(obj1)); // Move obj1's data into obj2

    std::cout << "obj2 data: ";
    for (int i : obj2.data) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
	return 0;
}
/*
 Move semantics in C++ is a feature introduced in C++11 that allows the resources owned by temporary objects to be moved rather than copied.
 Copy Constructor: Creates a deep copy of the array.
 Move Constructor: Transfers ownership of the array from the source object to the new object, leaving the source in a valid but empty state.
 Move Assignment Operator: Transfers ownership of the array from the source object to the current object, leaving the source in a valid but empty state.
 Move semantics are particularly useful when dealing with temporary objects that are about to be destroyed, as they allow the efficient 
 transfer of resources without the overhead of copying.

*/

class DynamicArray {
private:
    int* data;
    size_t size;

public:
    // Constructor
    DynamicArray(size_t size) : size(size), data(new int[size]) {
        std::cout << "Constructing DynamicArray\n";
    }

    // Destructor
    ~DynamicArray() {
        delete[] data;
        std::cout << "Destructing DynamicArray\n";
    }

    // Copy Constructor
    DynamicArray(const DynamicArray& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy Constructing DynamicArray\n";
    }

    // Move Constructor
    DynamicArray(DynamicArray&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
        std::cout << "Move Constructing DynamicArray\n";
    }

    // Copy Assignment Operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;

        delete[] data;
        size = other.size;
        data = new int[other.size];
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy Assigning DynamicArray\n";
        return *this;
    }

    // Move Assignment Operator
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
        std::cout << "Move Assigning DynamicArray\n";
        return *this;
    }
};
