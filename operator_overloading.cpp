/*
Operator overloading in C++ is a powerful feature that allows you to redefine the way operators work for user-defined types (like classes and structs). This makes your custom types behave more like built-in types, improving code readability and usability.
*/
class Vector {
public:
    int x, y;

    Vector(int x, int y) : x(x), y(y) {}

    Vector operator+(const Vector& other) {
        return Vector(x + other.x, y + other.y);
    }
};

/*
Commonly Overloaded Operators
Here are some commonly overloaded operators:

Arithmetic: +, -, *, /, %
Comparison: ==, !=, <, >, <=, >=
Assignment: =, +=, -=, etc.
Increment/Decrement: ++, --
Subscript: []
Function call: ()
Stream insertion/extraction: <<, >> (usually overloaded as friend functions)
/*
Member vs Friend Functions
Member function: Used when the left-hand operand is an object of the class.
Friend function: Used when you need access to private members but the left-hand operand is not an object of the class.
*/

class Vector {
public:
    int x, y;

    Vector(int x, int y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

/*
Important Points:
You cannot create new operators (like ** or %%).
Not all operators can be overloaded (e.g., ::, ., .*, sizeof, typeid).
Overloading should be intuitive and consistent with expected behavior.
*/
