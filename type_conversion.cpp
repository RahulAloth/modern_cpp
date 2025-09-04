/*
* Types of Type Conversion in Modern C++
* 1. Implicit Conversion(Type Coercion)
*/

int i = 42;
double d = i;  // int to double conversion
/*Explicit Conversion(Casting)
✅ C++ - Style Casts :
static_cast<T>(expr) – for well - defined conversions(e.g., int to double).
dynamic_cast<T>(expr) – for safe downcasting in polymorphic hierarchies.
const_cast<T>(expr) – to add / remove const qualifier.
reinterpret_cast<T>(expr) – for low - level, unsafe conversions(e.g., pointer to int).
*/
double pi = 3.14;
int im = static_cast<int>(pi);  // truncates to 3

/*
Modern C++ Enhancements
    1. explicit Keyword
    Used to prevent implicit conversions in constructors or conversion operators.
*/

class MyClass {
public:
    explicit MyClass(int x);  // prevents implicit conversion from int
};

/*
auto and decltype
These help with type inference, reducing the need for manual conversions.
*/

auto x = 42;// deduces int
/*
std::any, std::variant, std::optional
These types from the STL allow safer and more flexible type handling.
Best Practices in Modern C++
Prefer static_cast over C - style casts.
Use explicit to avoid unintended conversions.
Avoid reinterpret_cast unless absolutely necessary.
Use type inference(auto) to reduce verbosity and errors.
*/
