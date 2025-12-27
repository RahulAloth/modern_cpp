#include <iostream>
#include <string>
#include <type_traits>
#include <memory>
#include <utility>
#include <vector>

//
// 1. Introduction to Templates
//
template<typename T>
T add(T a, T b) {
    return a + b;
}

//
// 2. Template Argument Deduction & Instantiation
//
template<typename T>
void printType(T value) {
    std::cout << "Value: " << value << std::endl;
}

//
// 3. Explicit Specialization
//
template<typename T>
void printSpecial(T value) {
    std::cout << "General: " << value << std::endl;
}

template<>
void printSpecial<bool>(bool value) {
    std::cout << "Specialized for bool: " << (value ? "TRUE" : "FALSE") << std::endl;
}

//
// 4. Non-Type Template Arguments
//
template<int N>
void repeat() {
    for (int i = 0; i < N; i++)
        std::cout << "Hello (" << i << ")\n";
}

//
// 5 & 6. Perfect Forwarding
//
void process(int& x) {
    std::cout << "Lvalue processed: " << x << std::endl;
}

void process(int&& x) {
    std::cout << "Rvalue processed: " << x << std::endl;
}

template<typename T>
void forwarder(T&& arg) {
    process(std::forward<T>(arg));
}

//
// 7. Variadic Templates
//
template<typename... Args>
void log(Args... args) {
    (std::cout << ... << args) << std::endl;
}

//
// 8. Class Template
//
template<typename T>
class Box {
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
private:
    T value;
};

//
// 9. Class Template Explicit Specialization
//
template<>
class Box<bool> {
public:
    Box(bool v) : value(v) {}
    bool get() const { return value; }
private:
    bool value;
};

//
// 10. Class Template Partial Specialization
//
template<typename T>
class Wrapper {
public:
    void info() { std::cout << "General Wrapper\n"; }
};

template<typename T>
class Wrapper<T*> {
public:
    void info() { std::cout << "Pointer Wrapper\n"; }
};

//
// 11. Typedef, Type Alias, Alias Template
//
typedef std::vector<int> IntVec1;
using IntVec2 = std::vector<int>;

template<typename T>
using Vec = std::vector<T>;

//
// 12. Type Traits
//
template<typename T>
void checkType() {
    if constexpr (std::is_integral<T>::value)
        std::cout << "T is integral\n";
    else
        std::cout << "T is NOT integral\n";
}

//
// 13. static_assert
//
template<typename T>
void mustBeIntegral(T) {
    static_assert(std::is_integral<T>::value, "T must be an integral type");
}

//
// MAIN DEMO
//
int main() {
    std::cout << "\n=== 1. Templates ===\n";
    std::cout << add(3, 4) << std::endl;

    std::cout << "\n=== 2. Deduction ===\n";
    printType(42);

    std::cout << "\n=== 3. Explicit Specialization ===\n";
    printSpecial(10);
    printSpecial(true);

    std::cout << "\n=== 4. Non-Type Template Args ===\n";
    repeat<3>();

    std::cout << "\n=== 5 & 6. Perfect Forwarding ===\n";
    int x = 10;
    forwarder(x);        // lvalue
    forwarder(20);       // rvalue

    std::cout << "\n=== 7. Variadic Templates ===\n";
    log("A", " + ", 10, " + ", 2.5);

    std::cout << "\n=== 8. Class Template ===\n";
    Box<int> b1(100);
    std::cout << b1.get() << std::endl;

    std::cout << "\n=== 9. Explicit Specialization ===\n";
    Box<bool> b2(true);
    std::cout << b2.get() << std::endl;

    std::cout << "\n=== 10. Partial Specialization ===\n";
    Wrapper<int> w1;
    Wrapper<int*> w2;
    w1.info();
    w2.info();

    std::cout << "\n=== 11. Alias Templates ===\n";
    Vec<float> vf = {1.1, 2.2, 3.3};
    for (auto v : vf) std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "\n=== 12. Type Traits ===\n";
    checkType<int>();
    checkType<double>();

    std::cout << "\n=== 13. static_assert ===\n";
    mustBeIntegral(5);
    // mustBeIntegral(5.5); // Uncomment → compile-time error

    return 0;
}
