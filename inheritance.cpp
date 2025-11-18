/*
  inheritance.cpp

  Explanation of inheritance in modern C++ with a car example.

  Key concepts:
  - Inheritance allows a derived class to inherit members and methods from a base class.
  - Three access levels: public, protected, private.
  - public inheritance: "is-a" relationship; derived class is a specialized base class.
  - Use virtual functions for polymorphism (runtime dispatch).
  - Modern C++: use override keyword to mark virtual function overrides.
  - Prefer composition over inheritance when appropriate.
*/

#include <iostream>
#include <string>

// Base class
class Vehicle {
protected:
    std::string brand;
    int year;

public:
    Vehicle(const std::string& b, int y) : brand(b), year(y) {}

    virtual void display() const {
        std::cout << "Brand: " << brand << ", Year: " << year << '\n';
    }

    virtual void start() const {
        std::cout << "Vehicle starting...\n";
    }

    virtual ~Vehicle() = default;  // virtual destructor for proper cleanup
};

// Derived class: Car
class Car : public Vehicle {
private:
    int numDoors;

public:
    Car(const std::string& b, int y, int doors)
        : Vehicle(b, y), numDoors(doors) {}

    void display() const override {  // override keyword (C++11)
        Vehicle::display();
        std::cout << "Doors: " << numDoors << '\n';
    }

    void start() const override {
        std::cout << "Car engine starting...\n";
    }

    void honk() const {
        std::cout << "Beep beep!\n";
    }
};

// Another derived class: Motorcycle
class Motorcycle : public Vehicle {
private:
    bool hasStorage;

public:
    Motorcycle(const std::string& b, int y, bool storage)
        : Vehicle(b, y), hasStorage(storage) {}

    void display() const override {
        Vehicle::display();
        std::cout << "Storage: " << (hasStorage ? "Yes" : "No") << '\n';
    }

    void start() const override {
        std::cout << "Motorcycle engine roaring...\n";
    }
};

int main() {
    // Polymorphism: using base class pointers/references
    Vehicle* v1 = new Car("Toyota", 2023, 4);
    Vehicle* v2 = new Motorcycle("Harley-Davidson", 2022, true);

    std::cout << "=== Car ===\n";
    v1->display();
    v1->start();
    static_cast<Car*>(v1)->honk();

    std::cout << "\n=== Motorcycle ===\n";
    v2->display();
    v2->start();

    // Clean up
    delete v1;
    delete v2;

    // Alternative: stack allocation with references
    std::cout << "\n=== Stack-based example ===\n";
    Car myCar("Honda", 2024, 2);
    myCar.display();
    myCar.start();

    return 0;
}
// ...existing code...
