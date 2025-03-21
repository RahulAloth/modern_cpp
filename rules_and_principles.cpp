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
#include <utility>

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

/*
Single Responsibility Principle (SRP):

A class should have only one reason to change, meaning it should have only one job or responsibility.
Idea is simple, in the below example, instead of having one classfor user and doing file operation, we create two seperate clases.
Here, the User class is only responsible for managing user data, while the UserFileManager class is responsible for file operations. 
This way, each class has a single responsibility, adhering to the Single Responsibility Principle.
*/
class User {
private:
    std::string name;
    int age;
public:
    User(const std::string& name, int age) : name(name), age(age) {}

    std::string getName() const { return name; }
    int getAge() const { return age; }
};

class UserFileManager {
public:
    void saveToFile(const User& user, const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "Name: " << user.getName() << "\n";
            file << "Age: " << user.getAge() << "\n";
            file.close();
        }
    }
};

int user_main() {
    User user("Alice", 30);
    UserFileManager fileManager;
    fileManager.saveToFile(user, "user.txt");

    return 0;
}


/*
The Interface Segregation Principle(ISP) is one of the SOLID principles of object 
- oriented design.It states that clients should not be forced to depend on interfaces 
they do not use.This means that larger interfaces should be split into smaller, more
specific ones so that implementing classes only need to be concerned with the methods that are of interest to them.
*/
// Separate interfaces for different functionalities
class IPrinter {
public:
    virtual void print() = 0;
};

class IScanner {
public:
    virtual void scan() = 0;
};

// A class that only needs to print
class Printer : public IPrinter {
public:
    void print() override {
        cout << "Printing document..." << endl;
    }
};

// A class that only needs to scan
class Scanner : public IScanner {
public:
    void scan() override {
        cout << "Scanning document..." << endl;
    }
};

// A class that needs both printing and scanning functionalities
class MultiFunctionPrinter : public IPrinter, public IScanner {
public:
    void print() override {
        cout << "Printing document..." << endl;
    }
    void scan() override {
        cout << "Scanning document..." << endl;
    }
};

int isp_main() {
    Printer printer;
    Scanner scanner;
    MultiFunctionPrinter mfp;

    printer.print();
    scanner.scan();
    mfp.print();
    mfp.scan();

    return 0;
}
/*
The Dependency Inversion Principle (DIP) is another one of the SOLID principles.
It states that high-level modules should not depend on low-level modules. 
Both should depend on abstractions. Additionally, abstractions should not depend on details. 
Details should depend on abstractions.
Example:
*/
// Abstract interface for a database
class IDatabase {
public:
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual ~IDatabase() = default;
};

// Concrete implementation of a database
class MySQLDatabase : public IDatabase {
public:
    void connect() override {
        cout << "Connecting to MySQL database..." << endl;
    }
    void disconnect() override {
        cout << "Disconnecting from MySQL database..." << endl;
    }
};

// High-level module that depends on the abstract interface
class Application {
private:
    shared_ptr<IDatabase> database;
public:
    Application(shared_ptr<IDatabase> db) : database(db) {}
    void start() {
        database->connect();
        cout << "Application started." << endl;
    }
    void stop() {
        database->disconnect();
        cout << "Application stopped." << endl;
    }
};

int dip_main() {
    shared_ptr<IDatabase> db = make_shared<MySQLDatabase>();
    Application app(db);
    app.start();
    app.stop();
    return 0;
}
/*
The Rule of Zero in C++ suggests that classes should rely on automatic resource management 
and avoid defining custom destructors, copy/move constructors, or copy/move assignment operators.
This is achieved by using standard library facilities like smart pointers and containers,
which manage resources automatically.

In this example:

The Person class is a simple data holder with no custom resource management.
The Team class uses std::shared_ptr to manage Person objects, ensuring proper memory management without needing custom destructors or copy/move operations.
By following the Rule of Zero, the code is simpler, safer, and easier to maintain
*/

class Person {
public:
    std::string name;
    int age;

    Person(const std::string& name, int age) : name(name), age(age) {}
};

class Team {
private:
    std::vector<std::shared_ptr<Person>> members;
public:
    void addMember(const std::shared_ptr<Person>& person) {
        members.push_back(person);
    }

    void showMembers() const {
        for (const auto& member : members) {
            std::cout << member->name << " (" << member->age << " years old)" << std::endl;
        }
    }
};

int zero_main() {
    auto person1 = std::make_shared<Person>("Alice", 30);
    auto person2 = std::make_shared<Person>("Bob", 25);

    Team team;
    team.addMember(person1);
    team.addMember(person2);

    team.showMembers();

    return 0;
}
/*
The Rule of Three in C++ is a guideline that suggests if a class requires a user-defined destructor,
copy constructor, or copy assignment operator, it likely needs all three.
This rule helps manage resources properly and avoid issues like double deletion or resource leaks.
*/
class MyString {
private:
    char* data;
public:
    // Constructor
    MyString(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Destructor
    ~MyString() {
        delete[] data;
    }

    // Copy Constructor
    MyString(const MyString& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Copy Assignment Operator
    MyString& operator=(const MyString& other) {
        if (this == &other) return *this; // Self-assignment check

        delete[] data; // Free existing resource
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        return *this;
    }

    void print() const {
        std::cout << data << std::endl;
    }
};

int rule_3_main() {
    MyString str1("Hello");
    MyString str2 = str1; // Copy constructor
    MyString str3;
    str3 = str1; // Copy assignment operator

    str1.print();
    str2.print();
    str3.print();

    return 0;
}
/*
The Rule of Five in C++ is an extension of the Rule of Three.
It states that if a class requires a user-defined destructor, copy constructor,
or copy assignment operator, it likely also needs a user-defined move constructor
and move assignment operator. This rule helps manage resources efficiently, especially when dealing with dynamic memory or other resources.
*/
class Resource {
private:
    int* data;
public:
    // Constructor
    Resource(int value) : data(new int(value)) {
        std::cout << "Resource acquired\n";
    }

    // Destructor
    ~Resource() {
        delete data;
        std::cout << "Resource destroyed\n";
    }

    // Copy Constructor
    Resource(const Resource& other) : data(new int(*other.data)) {
        std::cout << "Resource copied\n";
    }

    // Copy Assignment Operator
    Resource& operator=(const Resource& other) {
        if (this == &other) return *this; // Self-assignment check
        delete data;
        data = new int(*other.data);
        std::cout << "Resource assigned\n";
        return *this;
    }

    // Move Constructor
    Resource(Resource&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Resource moved\n";
    }

    // Move Assignment Operator
    Resource& operator=(Resource&& other) noexcept {
        if (this == &other) return *this; // Self-assignment check
        delete data;
        data = other.data;
        other.data = nullptr;
        std::cout << "Resource move-assigned\n";
        return *this;
    }

    void print() const {
        if (data) {
            std::cout << "Resource value: " << *data << std::endl;
        } else {
            std::cout << "Resource is empty\n";
        }
    }
};

int rule_5_main() {
    Resource res1(10);
    Resource res2 = res1; // Copy constructor
    Resource res3(20);
    res3 = res1; // Copy assignment operator

    Resource res4 = std::move(res1); // Move constructor
    Resource res5(30);
    res5 = std::move(res3); // Move assignment operator

    res2.print();
    res4.print();
    res5.print();

    return 0;
}
