## 2.5 Template Enhancements

Modern C++ introduced several powerful improvements to templates, making generic programming more expressive, safer, and easier to write.  
C++11, C++14, C++17, and C++20 expanded template capabilities with:

- Variadic templates (C++11)
- Fold expressions (C++17)
- Template aliases (C++11)
- Concepts & constraints (C++20)

These features reduce boilerplate, improve readability, and enable more robust compile‑time logic.

---

### 2.5.1 Variadic Templates (C++11)

Variadic templates allow a template to accept **zero or more** parameters.  
They are the foundation of modern generic programming.

#### Motivation
Before C++11, templates could not naturally accept an arbitrary number of arguments.

#### Modern C++ Solution

```cpp
template <typename... Args>
void print_all(const Args&... args) {
    (std::cout << ... << args) << '\n';
}
```

#### Key Concepts

Args... → template parameter pack

args... → function parameter pack

Packs can be expanded recursively or using fold expressions

#### Recursive Example

```cpp
template <typename T>
void print_one(const T& t) {
    std::cout << t << '\n';
}

template <typename T, typename... Rest>
void print_one(const T& t, const Rest&... rest) {
    std::cout << t << '\n';
    print_one(rest...);
}
```

### 2.5.2 Fold Expressions (C++17)

Fold expressions provide a clean way to reduce a parameter pack using an operator.

Motivation
Before C++17, variadic templates required recursive unpacking.

Modern C++ Solution

```cpp
template <typename... Args>
auto sum(const Args&... args) {
    return (args + ...);   // unary right fold
}
```

Types of Folds
Unary left fold: (... op args)

Unary right fold: (args op ...)

Binary fold: (args op ... op init)

Example: Logical AND

```cpp
template <typename... Bools>
bool all_true(Bools... bs) {
    return (... && bs);
}
```

### 2.5.3 Template Aliases (C++11)
Template aliases allow you to create readable, reusable names for complex templates.

Motivation
typedef could not alias templates.

Modern C++ Solution

```cpp
template <typename T>
using Vec = std::vector<T>;

Vec<int> v = {1, 2, 3};
```
####  Example: Smart Pointer Alias

```cpp
template <typename T>
using Ptr = std::unique_ptr<T>;

Ptr<double> p = std::make_unique<double>(3.14);
```
### 2.5.4 Concepts & Constraints (C++20)
Concepts introduce compile‑time type checking for templates, replacing SFINAE with readable constraints.

Motivation
Before C++20, template errors were cryptic and hard to debug.

Modern C++ Solution

```cpp
#include <concepts>

template <std::integral T>
T add(T a, T b) {
    return a + b;
}
```

Custom Concept Example

```cpp
template <typename T>
concept Printable = requires(T x) {
    std::cout << x;
};

template <Printable T>
void print(const T& value) {
    std::cout << value << '\n';
}
```

### Summary of Template Enhancements

| Feature                | Introduced | Purpose                               | Benefit                                      |
|------------------------|------------|----------------------------------------|----------------------------------------------|
| Variadic templates     | C++11      | Accept arbitrary number of parameters  | Foundation of modern generic programming     |
| Fold expressions       | C++17      | Reduce parameter packs cleanly         | Removes recursion, cleaner syntax            |
| Template aliases       | C++11      | Alias complex template types           | Improves readability and reuse               |
| Concepts & constraints | C++20      | Constrain template parameters          | Safer, clearer, more expressive templates    |



---

If you want, I can now generate **2.6 Smart Pointers** in the same Markdown style.









