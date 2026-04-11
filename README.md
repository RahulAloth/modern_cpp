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
### Chapter 1
- [`01 Towards Modern CPP`](/towards_modern_cpp.md)
### Chapter Index
- Why Modern C++
- Removed/Deprecated C++98/03 features
- C compatibility considerations
- Overview of new paradigms (RAII, templates, type inference)

---

## Chapter 2 — Language Usability Enhancements
### Chapter 2
- [`02 Language Usability Enhancements`](/02_language_usability_enhancement.md)
- [`02_usability_enhancement_chapter extension`](/02_usability_enhancement_ext.md)

### Chapter Index
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

# Chapter 15 — Value Categories & Expressions

### Chapter Index
- lvalues, rvalues, glvalues, xvalues, prvalues  
- Expression categories and their impact  
- Reference collapsing rules  
- How value categories affect:
  - auto
  - decltype
  - forwarding references
  - overload resolution  
- Practical examples and pitfalls  

---

# Chapter 16 — C++ Memory Model & Atomics

### Chapter Index
- Data races & undefined behavior  
- Atomic types (`std::atomic<T>`)  
- Memory ordering:
  - relaxed  
  - acquire / release  
  - acq_rel  
  - seq_cst  
- Fences & synchronization  
- Lock‑free programming basics  
- Designing thread‑safe code  

---

# Chapter 17 — Exception Safety & Guarantees

### Chapter Index
- Basic, strong, and no‑throw guarantees  
- RAII and exception‑safe design  
- noexcept correctness  
- Exception‑safe container operations  
- Writing robust APIs  
- Error propagation strategies  

---

# Chapter 18 — Advanced Templates & Metaprogramming

### Chapter Index
- SFINAE (expression‑based and type‑based)  
- Tag dispatching  
- CRTP (Curiously Recurring Template Pattern)  
- Template specialization best practices  
- Non‑type template parameters (NTTP) evolution  
- Concepts & requires‑clauses patterns  
- Compile‑time polymorphism  
- TMP utilities and idioms  

---

# Chapter 19 — Filesystem Library (C++17)

### Chapter Index
- `std::filesystem::path`  
- Directory iteration  
- File operations (copy, move, remove)  
- Permissions and status queries  
- Portable path handling  
- Practical examples  

---

# Chapter 20 — Chrono Library Deep Dive

### Chapter Index
- `std::chrono::duration`  
- `std::chrono::time_point`  
- Clocks (system, steady, high‑resolution)  
- Time conversions  
- Formatting time (C++20)  
- Chrono user‑defined literals (`10ms`, `2h`)  
- Real‑world usage patterns  

---

# Chapter 21 — Random Number Facilities (C++11)

### Chapter Index
- Engines (`std::mt19937`, `random_device`)  
- Distributions (uniform, normal, bernoulli, etc.)  
- Seeding strategies  
- Reproducible randomness  
- Best practices for simulations and games  

---

# Chapter 22 — Modern Formatting & Text Handling

### Chapter Index
- `std::format` (C++20)  
- `std::print` (C++23)  
- Format specifiers  
- UTF‑8 improvements  
- `std::string_view` deep dive  
- Efficient string handling patterns  

---

# Summary of New High‑Priority Chapters

| Chapter | Topic |
|--------|--------|
| 15 | Value Categories & Expressions |
| 16 | Memory Model & Atomics |
| 17 | Exception Safety & Guarantees |
| 18 | Advanced Templates & Metaprogramming |
| 19 | Filesystem Library |
| 20 | Chrono Library |
| 21 | Random Number Facilities |
| 22 | Modern Formatting & Text Handling |

## Design Patern:

Refer : https://metapatterns.io/

