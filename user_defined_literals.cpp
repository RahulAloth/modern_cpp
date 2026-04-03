/*
    User-Defined Literals (UDLs) in Modern C++
    ------------------------------------------

    User-defined literals allow programmers to attach custom suffixes to literal
    values (numbers, strings, characters) to give them semantic meaning.

    Introduced in:  C++11
    Enhanced in:    C++14 (template UDLs)
                    C++17 (string_view, filesystem)
                    C++20 (constexpr std::string, constexpr containers)

    Benefits:
        - More expressive and readable code
        - Zero-cost abstractions
        - Strong typing for units and domain-specific values
        - Compile-time parsing (e.g., binary literals)

    Categories of UDLs:
        1. Integer literals:        operator"" _x(unsigned long long)
        2. Floating-point literals: operator"" _x(long double)
        3. Character literals:      operator"" _x(char)
        4. String literals:         operator"" _x(const char*, size_t)
        5. Template UDLs (C++14):   operator"" _x<Chars...>()

    Standard Library UDLs:
        - <chrono>         → 10s, 500ms, 2h
        - <string>         → "hello"s
        - <string_view>    → "hello"sv
        - <complex>        → 3.0i
        - <filesystem>     → "path"_p
*/

#include <iostream>
#include <string>
#include <string_view>
#include <chrono>
#include <complex>
#include <filesystem>

//
// -----------------------------------------------------------------------------
// 1. Floating-Point Unit Literals (_km, _m)
// -----------------------------------------------------------------------------

[[nodiscard]] constexpr long double operator"" _km(long double val) {
    return val * 1000.0L;   // kilometers → meters
}

[[nodiscard]] constexpr long double operator"" _m(long double val) {
    return val;             // identity
}

//
// -----------------------------------------------------------------------------
// 2. Integer Literal UDL (_id)
// -----------------------------------------------------------------------------

[[nodiscard]] constexpr unsigned long long operator"" _id(unsigned long long v) {
    return v; // could wrap in a strong type
}

//
// -----------------------------------------------------------------------------
// 3. Character Literal UDL (_ascii)
// -----------------------------------------------------------------------------

[[nodiscard]] constexpr int operator"" _ascii(char c) {
    return static_cast<int>(c);
}

//
// -----------------------------------------------------------------------------
// 4. Strong Type Example: Meter
// -----------------------------------------------------------------------------

struct Meter {
    long double value;
};

[[nodiscard]] constexpr Meter operator"" _meter(long double v) {
    return Meter{v};
}

[[nodiscard]] constexpr Meter operator+(Meter a, Meter b) {
    return Meter{a.value + b.value};
}

//
// -----------------------------------------------------------------------------
// 5. Template UDL (C++14): Convert string literal → std::string
// -----------------------------------------------------------------------------

template<char... Chars>
constexpr std::string operator"" _s() {
    return std::string{Chars...};
}

//
// -----------------------------------------------------------------------------
// 6. Binary Literal Parser (C++14)
// -----------------------------------------------------------------------------

template<char... Chars>
constexpr int operator"" _bin() {
    int result = 0;
    for (char c : {Chars...}) {
        result <<= 1;
        static_assert(c == '0' || c == '1', "Invalid binary digit in _bin literal");
        result |= (c - '0');
    }
    return result;
}

//
// -----------------------------------------------------------------------------
// 7. Standard Library UDLs
// -----------------------------------------------------------------------------

using namespace std::chrono_literals;       // 10s, 500ms, 2h
using namespace std::string_literals;       // "hello"s
using namespace std::string_view_literals;  // "hello"sv
using namespace std::complex_literals;      // 3.0i
using namespace std::filesystem;            // "path"_p

//
// -----------------------------------------------------------------------------
// MAIN DEMONSTRATION
// -----------------------------------------------------------------------------

int main() {

    // --- Floating-point UDLs ---
    long double dist = 5.0_km + 300.0_m;
    std::cout << "Distance in meters: " << dist << "\n";

    // --- Integer UDL ---
    auto user = 123_id;
    std::cout << "User ID: " << user << "\n";

    // --- Character UDL ---
    int code = 'A'_ascii;
    std::cout << "ASCII of 'A': " << code << "\n";

    // --- Strong type UDL ---
    Meter a = 2.0_meter;
    Meter b = 3.5_meter;
    Meter c = a + b;
    std::cout << "Strong type meters: " << c.value << "\n";

    // --- Template string UDL ---
    auto name = "Aloth"_s;
    std::cout << "Name: " << name << "\n";

    // --- Standard library string UDL ---
    auto s = "Hello"s;
    std::cout << "std::string literal: " << s << "\n";

    // --- String_view UDL ---
    auto sv = "World"sv;
    std::cout << "std::string_view literal: " << sv << "\n";

    // --- Chrono UDLs ---
    auto timeout = 10s;
    auto interval = 500ms;
    std::cout << "Timeout (s): " << timeout.count() << "\n";
    std::cout << "Interval (ms): " << interval.count() << "\n";

    // --- Complex number UDL ---
    auto z = 3.0 + 4.0i;
    std::cout << "Complex number: " << z << "\n";

    // --- Filesystem path UDL ---
    auto path = "config.json"_p;
    std::cout << "Filesystem path: " << path << "\n";

    // --- Binary literal ---
    constexpr int val = "1011"_bin;  // 11
    std::cout << "Binary 1011 = " << val << "\n";

    return 0;
}
