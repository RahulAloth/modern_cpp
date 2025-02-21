L-Value                                             |      R-Value
.............................................................................................................
L-Value has a name	                                |      R-Value does not have a name
All variables are l-values	                        |      R-Value is a temporary value
Can be assigned values	                            |      R-Value cannot be assigned values
Some expressions return l-values	                  |      Some expressions return r-values
L-Value persists beyond the expression	            |      R-Value does not persist beyond the expression
Functions that return by reference return l-values	|      Functions that return by value return r-values
Reference to l-value (called l-value reference)	    |      Reference to r-value (called r-value reference)
.............................................................................................................

#include <iostream>

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

