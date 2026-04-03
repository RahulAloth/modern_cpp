# Chapter 2 — Language Usability Enhancements

Modern C++ introduced a wide range of usability improvements that make code safer, clearer, and more expressive. This chapter focuses on three foundational enhancements: `nullptr`, `constexpr` (from C++11 through C++20), and user‑defined literals. Each of these features addresses long‑standing pain points in C++98/03 and helps developers write more robust and maintainable code.

---

## 2.1 Constants & Literals

Constants and literal values are fundamental to any programming language. Modern C++ significantly expands how constants are expressed, evaluated, and customized.

This section explores:
- The introduction of `nullptr` as a type‑safe null pointer  
- The evolution of `constexpr` from C++11 to C++20  
- The power and flexibility of user‑defined literals  

---

## nullptr

### Motivation
Before C++11, null pointers were represented using the macro `NULL`, typically defined as `0` or `((void*)0)`. This caused several issues:
- Ambiguity in overload resolution  
- Accidental selection of integer overloads  
- Lack of type safety  

### The `nullptr` Keyword
C++11 introduced `nullptr` as a dedicated null pointer literal with its own type: `std::nullptr_t`.

### Key Properties
- **Type‑safe**: Cannot be implicitly converted to integers  
- **Unambiguous**: Overload resolution always selects pointer overloads  
- **Consistent**: Works uniformly across all pointer types  

### Example
```cpp
void f(int);
void f(char*);

f(0);        // Calls f(int)
f(nullptr);  // Calls f(char*)
