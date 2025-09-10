/* Traditional enum
A traditional enum is a simple way to define a group of related constants.
*/

enum Color {
    Red,
    Green,
    Blue
};

Color c = Red;
int x = c; // OK: implicit conversion

/*
Key Characteristics:
Implicitly converted to int: You can assign an enum value to an int without a cast.
Global scope pollution: The names (Red, Green, Blue) are injected into the surrounding/enclosing scope.
No type safety: You can accidentally assign any integer to a variable of type Color.
Underlying Type: Usually int, but can be specified in C++11 and later.
Drawbacks:
Name collisions in large codebases.
Lack of type safety can lead to bugs.


In C++, enum and scoped enum (also known as enum class) are used to define a set of named integral constants, but they differ significantly in terms of scope, type safety, and implicit conversions

Scoped Enum (enum class)
Introduced in C++11, scoped enums solve many of the problems of traditional enums.
*/
enum class Color {
    Red,
    Green,
    Blue
};
/*
Characteristics:
Scoped: Enumerators are scoped to the enum name. You must use Color::Red, etc.
No Implicit Conversion: Cannot implicitly convert to int.
Strongly Typed: Prevents accidental misuse.
Custom Underlying Type: You can specify the underlying type (e.g., enum class Color : uint8_t).
*/
enum class Color { Red, Green, Blue };

Color c = Color::Red;
// int x = c; // ❌ Error: no implicit conversion
int x = static_cast<int>(c); // ✅ Explicit conversion
