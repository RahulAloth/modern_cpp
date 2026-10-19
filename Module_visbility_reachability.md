# Visibility vs Reachability in C++ Modules

## Introduction

One of the most important concepts in C++ Modules is the distinction between **visibility** and **reachability**.

Many developers assume:

> If a type or function is not exported, it cannot be used outside the module.

This is not always true.

A declaration might be:

- Visible and reachable
- Reachable but not visible
- Neither visible nor reachable

Understanding this distinction is essential for correctly designing module interfaces.

---

# Visibility

## Definition

Visibility answers the question:

> Can the compiler see and refer to the name directly?

If a declaration is exported, its name becomes visible outside the module.

Example:

```cpp
export module maths;

export struct Employee
{
    std::string name;
    int id;
};
```

Consumer:

```cpp
import maths;

Employee emp;
```

This compiles successfully because the name:

```cpp
Employee
```

is visible outside the module.

---

# Reachability

## Definition

Reachability answers the question:

> Can the compiler still use the entity indirectly?

An entity may not be visible by name but may still participate in compilation through an exported interface.

---

# Visibility vs Reachability

## Memory Trick

```text
Visibility  = Can I say its name?

Reachability = Can I still use it indirectly?
```

---

# Example 1: Exported Function

Module:

```cpp
export module maths;

export int square(int x)
{
    return x * x;
}
```

Consumer:

```cpp
import maths;

square(5);
```

Result:

```text
Visible   -> Yes
Reachable -> Yes
```

Because the function is exported.

---

# Example 2: Non-Exported Function

Module:

```cpp
export module maths;

int add(int a, int b)
{
    return a + b;
}
```

Consumer:

```cpp
import maths;

add(2, 3);
```

Result:

```text
Compile Error
```

Why?

Because:

```text
add() is not exported
```

Therefore:

```text
Visible   -> No
Reachable -> No
```

outside the module.

---

# Exporting an Entire Namespace

Instead of exporting every function individually:

```cpp
export int square(int);
export int cube(int);
```

you can export a namespace.

```cpp
export namespace maths
{
    int square(int);
    int cube(int);
}
```

Consumer:

```cpp
maths::square(5);
maths::cube(3);
```

Both functions are visible.

---

# Selective Export Within Namespace

You can choose which entities to export.

```cpp
namespace maths
{
    int add(int, int);

    export int square(int);
    export int cube(int);
}
```

Consumer:

```cpp
maths::square(5);   // OK
maths::cube(5);     // OK
maths::add(5,3);    // ERROR
```

Result:

```text
Namespace visible
add() not visible
```

---

# Exporting Different C++ Types

Modules can export almost any C++ entity.

Examples:

```cpp
export class Person;
export struct Employee;
export enum Color;
export union Data;
export namespace maths;
export template<typename T> class Vector;
```

---

# Employee Example

Consider the following module:

```cpp
export module maths;

struct Employee
{
    std::string name;
    int id;
};

export Employee createEmployee(
    std::string name,
    int id)
{
    return {name, id};
}
```

Notice:

```cpp
Employee
```

is NOT exported.

---

# Attempting Direct Use

Consumer:

```cpp
import maths;

Employee emp;
```

Result:

```text
Compile Error
```

The compiler reports:

```text
Employee undeclared identifier
```

Why?

Because:

```text
Employee is not visible.
```

---

# Using auto Instead

Consumer:

```cpp
import maths;

auto emp =
    createEmployee("Rahul", 101);
```

This works.

Why?

Because:

```cpp
createEmployee()
```

is exported.

The compiler understands the return type internally.

Therefore:

```text
Employee is reachable
Employee is not visible
```

---

# What Happens Here?

The object exists.

The compiler knows its complete type information.

However, the name:

```cpp
Employee
```

cannot be written directly by the client.

The compiler deduces the type using:

```cpp
auto
```

This is a classic example of:

```text
Reachable but Not Visible
```

---

# Visual Representation

## Case 1: Exported Type

```text
Module
 ├── Employee
 └── createEmployee()

export Employee
export createEmployee()
```

Client Can Use:

```cpp
Employee emp;
auto e = createEmployee();
```

Result:

```text
Visible   -> Yes
Reachable -> Yes
```

---

## Case 2: Non-Exported Type Returned by Exported Function

```text
Module
 ├── Employee
 └── createEmployee()

Employee        -> Not Exported
createEmployee  -> Exported
```

Client Can Use:

```cpp
auto e = createEmployee();
```

Client Cannot Use:

```cpp
Employee e;
```

Result:

```text
Visible   -> No
Reachable -> Yes
```

---

# Why auto Works

This code fails:

```cpp
Employee e = createEmployee();
```

because:

```text
Employee name is hidden.
```

However:

```cpp
auto e = createEmployee();
```

works because:

```text
The compiler deduces the type
without needing the type name.
```

The type remains reachable through the exported function.

---

# Visibility Matrix

| Entity | Visible | Reachable |
|----------|----------|----------|
| Exported Type | Yes | Yes |
| Exported Function | Yes | Yes |
| Non-Exported Function | No | No |
| Non-Exported Type Returned By Exported Function | No | Yes |
| Type In Private Module Fragment | No | No |

---

# Private Module Fragment

C++ Modules provide a mechanism to completely hide implementation details.

Example:

```cpp
export module maths;

export int square(int);

module : private;

struct Employee
{
};
```

Now the type:

```cpp
Employee
```

is:

```text
Not Visible
Not Reachable
```

from outside the module.

Even indirect use is prevented.

---

# Key Takeaways

- Visibility means a declaration's name can be referenced outside the module.
- Reachability means a declaration can still participate in compilation indirectly.
- Exported entities are both visible and reachable.
- Non-exported entities are usually hidden.
- A non-exported type may still be reachable through an exported function.
- `auto` often allows use of reachable-but-not-visible types.
- Private module fragments can make entities completely invisible and unreachable.

---

# Interview Questions

## What is Visibility?

Visibility means a declaration's name can be used outside the module.

Example:

```cpp
export struct Employee {};
```

The name `Employee` is visible.

---

## What is Reachability?

Reachability means an entity can still be used indirectly even if its name is hidden.

Example:

```cpp
struct Employee {};

export Employee createEmployee();
```

This works:

```cpp
auto emp = createEmployee();
```

Even though:

```cpp
Employee emp;
```

does not compile.

---

## Can a Type Be Reachable but Not Visible?

Yes.

A non-exported type returned by an exported function is a classic example.

---

## Does Non-Exported Mean Unusable?

No.

A non-exported type may still be reachable through exported APIs.

Only entities inside a private module fragment can be completely hidden.
