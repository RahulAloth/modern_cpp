# modern_cpp
This project encompasses learning topics for C++11, C++14, C++17, and C++20, including Concurrency and Design Patterns in Modern C++. It can be forked and used as a learning reference for newcomers who want to learn C++ and Algorithms.

# 📘 Modern C++ (C++11 → C++23) — Chapter Index

## Preface
- What is Modern C++
- Evolution from C++98/03 to C++23
- Philosophy: safety, expressiveness, performance
- Deprecated features and migration notes

---

## Chapter 1 — Towards Modern C++
- Why Modern C++
- Removed/Deprecated C++98/03 features
- C compatibility considerations
- Overview of new paradigms (RAII, templates, type inference)

---

## Chapter 2 — Language Usability Enhancements

### 2.1 Constants & Literals
- `nullptr`
- `constexpr` (C++11 → C++20 evolution)
- User‑defined literals

### 2.2 Variables & Initialization
- Uniform initialization `{}` 
- Initializer lists
- Structured bindings (C++17)
- Inline variables (C++17)

### 2.3 Type Inference
- `auto`
- `decltype`
- `decltype(auto)`
- Return type deduction

### 2.4 Control Flow Improvements
- Range‑based for loops
- `if`/`switch` with initializer
- `if constexpr` (C++17)

### 2.5 Template Enhancements
- Variadic templates
- Fold expressions (C++17)
- Template aliases
- Concepts & constraints (C++20)

---

## Chapter 3 — Smart Pointers & Memory Management
- `unique_ptr`
- `shared_ptr`
- `weak_ptr`
- Custom deleters
- Ownership semantics
- Avoiding memory leaks & dangling pointers

---

## Chapter 4 — Move Semantics & Perfect Forwarding
- Rvalue references
- Move constructors & move assignment
- `std::move` vs `std::forward`
- Universal/forwarding references

---

## Chapter 5 — Modern Class Design
- Defaulted & deleted functions
- Delegating constructors
- In‑class member initializers
- Explicit conversion operators
- Rule of 0 / Rule of 3 / Rule of 5

---

## Chapter 6 — Functional Programming Tools
- Lambda expressions
- Generic lambdas (C++14)
- Capture modes
- `std::function`, binders, callable wrappers
- Lambda templates (C++20)

---

## Chapter 7 — Concurrency & Parallelism
- `std::thread`
- Mutexes, locks, condition variables
- Futures, promises, `std::async`
- Atomics & memory ordering
- Parallel STL (C++17)
- Coroutines (C++20)

---

## Chapter 8 — Containers & Iterators
- New STL containers (`std::array`, `std::forward_list`)
- Container improvements
- Node‑handle API (C++17)
- Views & ranges (C++20)
- Iterator improvements

---

## Chapter 9 — Error Handling & Diagnostics
- Exceptions
- `noexcept`
- `std::optional`
- `std::variant`
- `std::any`
- Contracts (proposed)

---

## Chapter 10 — Compile‑Time Programming
- `constexpr` deep dive
- Constant evaluation rules
- Template metaprogramming
- Concepts & constraints (C++20)
- `consteval` & `constinit` (C++20)

---

## Chapter 11 — Modules (C++20)
- Why modules replace headers
- Import/export syntax
- Module partitions
- Build system considerations
- Migration from header‑based builds

---

## Chapter 12 — Ranges (C++20)
- Range concepts
- Views
- Range adaptors
- Pipeline syntax
- Custom range adaptors

---

## Chapter 13 — Coroutines & Async Programming
- Coroutine primitives (`co_await`, `co_yield`, `co_return`)
- Awaitables & executors
- Generator patterns
- Asynchronous design patterns
- Networking TS overview

---

## Chapter 14 — New Features in C++23
- `std::expected`
- `std::mdspan`
- `std::print`
- More `constexpr` library components
- Pattern matching (if included in your reference)
- Improved ranges & views

---

## Appendices
- Quick reference tables
- Compiler support matrix
- Migration guide (C++98 → C++23)
- Best practices & idioms

## Design Patern:

Refer : https://metapatterns.io/

