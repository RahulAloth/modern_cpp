/*
In C++, constexpr is a keyword used to indicate that the value of a variable or
the result of a function can be evaluated at compile time. This can lead to performance improvements and more robust code by catching errors early.

🔹 Key Uses of constexpr
Constant Variables:
constexpr int maxSize = 100;
This defines a constant that the compiler evaluates at compile time.

Constant Expressions in Functions:
*/
constexpr int square(int x) {
    return x * x;
}

int arr[square(5)]; // OK: square(5) is evaluated at compile time

// User-Defined Types: You can use constexpr constructors and member functions in classes:
struct Point {
    int x, y;
    constexpr Point(int x, int y) : x(x), y(y) {}
    constexpr int sum() const { return x + y; }
};
constexpr Point p(3, 4);
static_assert(p.sum() == 7, "Compile-time check");

With if constexpr (C++17 and later): Enables compile-time branching:
template<typename T>
void printType() {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Integral type\n";
    } else {
        std::cout << "Non-integral type\n";
    }
}
/*
Example:
Scenario: Compile-Time Distance Calculation Between Two GPS Coordinates
Suppose you're working on a GPS navigation system where you frequently calculate 
distances between fixed landmarks. You can use constexpr to compute these distances at compile time instead of runtime.
*/
#include <iostream>
#include <cmath>

constexpr double toRadians(double degrees) {
    return degrees * 3.14159265358979323846 / 180.0;
}

constexpr double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    double a = std::pow(std::sin(dLat / 2), 2) +
               std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
               std::pow(std::sin(dLon / 2), 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double radius = 6371.0; // Earth's radius in kilometers

    return radius * c;
}

// Compile-time distance between two fixed landmarks
constexpr double distanceToMunich = haversine(48.137154, 11.576124, 48.208174, 16.373819); // Munich to Vienna

int main() {
    std::cout << "Distance from Munich to Vienna: " << distanceToMunich << " km\n";
    return 0;
}
