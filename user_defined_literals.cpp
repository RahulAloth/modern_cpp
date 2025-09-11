/*
User-defined literals (UDLs) in C++ are a powerful feature introduced in C++11 and enhanced in C++14 that allow 
programmers to define custom behavior for literal values (like numbers, strings, etc.) by attaching a suffix to them.
This makes code more expressive and readable.
What Are User-Defined Literals?

Syntax Overview
User-defined literals are defined using special functions with the operator"" syntax.

Types of UDLs:
Integer literals (unsigned long long)
Floating-point literals (long double)
Character literals (char)
String literals (const char*, const wchar_t*, etc.)
Raw string literals (const char*, etc.)

Example:
*/
#include <iostream>

constexpr long double operator"" _km(long double val) {
    return val * 1000;
}

constexpr long double operator"" _m(long double val) {
    return val;
}

int main() {
    long double dist = 5.0_km + 300.0_m;
    std::cout << "Distance in meters: " << dist << std::endl;
}

/*
C++14 and Beyond: UDLs with constexpr and Templates
C++14 allows UDLs to be defined using template literals, which makes them more flexible:
*/

#include <string>

template<char... Chars>
std::string operator"" _s() {
    return std::string{Chars...};
}

auto name = "Aloth"_s;  // creates a std::string
/*
Use Cases
Units of measurement (e.g., _km, _kg)
Time durations (e.g., 10s, 5min with <chrono>)
String manipulation (e.g., converting to std::string)
Custom types (e.g., currency, domain-specific types)

Real-World Use Case: std::chrono
The <chrono> library uses UDLs extensively:
*/

#include <chrono>
using namespace std::chrono_literals;

auto timeout = 10s;  // 10 seconds
auto interval = 500ms;  // 500 milliseconds


#include <iostream>

// Template literal operator for binary strings
template<char... Chars>
constexpr int operator"" _bin() {
    constexpr char str[] = {Chars..., '\0'};
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        result <<= 1;
        if (str[i] == '1') result |= 1;
        else if (str[i] != '0') throw "Invalid binary digit";
    }
    return result;
}

int main() {
    constexpr int val = "1011"_bin;  // binary 1011 = decimal 11
    std::cout << "Binary 1011 is: " << val << std::endl;
}

