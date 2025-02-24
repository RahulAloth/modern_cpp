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
