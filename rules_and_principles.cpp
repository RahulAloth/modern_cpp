/*
In this chapter, describing some of the Principles used in c++ Programming.

Liskov Substitution Principle (LSP):
Objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program.
In this example, the move method is defined in the base class Bird and overridden in the derived classes Sparrow and Penguin.
The letBirdMove function can accept any object of type Bird or its subclasses, and it will call the appropriate move method
based on the actual object type. This adheres to the Liskov Substitution Principle because Sparrow and Penguin can be used interchangeably with Bird without causing any issues.
Example:
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Bird {
public:
    virtual std::string move() const {
        return "Moving";
    }
};

class Sparrow : public Bird {
public:
    std::string move() const override {
        return "Flying high";
    }
};

class Penguin : public Bird {
public:
    std::string move() const override {
        return "Swimming";
    }
};

void letBirdMove(const Bird& bird) {
    std::cout << bird.move() << std::endl;
}

int rules_main() {
    Sparrow sparrow;
    Penguin penguin;

    letBirdMove(sparrow);  // Output: Flying high
    letBirdMove(penguin);  // Output: Swimming

    return 0;
}
/*
Open/Closed Principle (OCP):
Software entities (classes, modules, functions, etc.) should be open 
for extension but closed for modification.The Open/Closed Principle (OCP) 
states that software entities (classes, modules, functions, etc.) should be open 
for extension but closed for modification. This means you should be able to add new 
functionality without changing existing code.
*/



class Shape {
public:
    virtual double area() const = 0; // Pure virtual function
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

double totalArea(const std::vector<std::shared_ptr<Shape>>& shapes) {
    double total = 0;
    for (const auto& shape : shapes) {
        total += shape->area();
    }
    return total;
}

int open_close_main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0));
    shapes.push_back(std::make_shared<Rectangle>(4.0, 6.0));

    std::cout << "Total Area: " << totalArea(shapes) << std::endl;

    return 0;
}
/*
In this example, the Shape class is an abstract base class with a pure virtual function area().
The Circle and Rectangle classes inherit from Shape and implement the area() function.
The totalArea function calculates the total area of a collection of shapes.
This function works with any class that inherits from Shape and implements the area() function.
If you want to add a new shape, like a Triangle, you can do so without modifying the existing code:
*/

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const override {
        return 0.5 * base * height;
    }
};

int open_close_main_ext() {
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0));
    shapes.push_back(std::make_shared<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_shared<Triangle>(3.0, 4.0));

    std::cout << "Total Area: " << totalArea(shapes) << std::endl;

    return 0;
}
