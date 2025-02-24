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

#include <iostream>
#include <utility> // for std::move

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
