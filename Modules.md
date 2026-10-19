# C++20 Modules

## Introduction

**Modules** are a feature introduced in **C++20** as an alternative to the traditional header-based approach for organizing and reusing code.

They were designed to address several common problems associated with header files, including:

- Repeated inclusion of the same code
- Increased compilation times
- Macro leakage across translation units
- Complex dependency management

Unlike header files, modules are compiled separately and can be imported by other source files without repeatedly processing the same textual content.

---

# Benefits of Modules

## 1. Improved Compilation Performance

Modules can reduce compilation time because:

- Source code is compiled once.
- Other files import the compiled module interface.
- Repeated parsing of header contents is avoided.

This benefit becomes more significant in large projects with many dependencies.

---

## 2. Better Encapsulation

Modules allow developers to explicitly control which declarations are visible outside the module.

Features:

- Export only intended declarations.
- Keep internal implementation details hidden.
- Improve maintainability and modularity.

This level of explicit visibility control is not available with traditional header files.

---

## 3. Flexible Organization

Modules support:

- Interface declarations
- Implementation code
- Separate implementation units (optional)

A developer may still separate declarations and implementations if desired.

---

# Important Note

Modules do **not completely replace header files**.

Header files continue to play an important role, especially when:

- Working with existing libraries
- Using legacy code
- Including functionality that is not yet modularized

As a result, modern C++ projects may use both modules and headers together.

---

# Structure of a C++ Module

A module can contain up to four sections.

## 1. Global Module Fragment (Optional)

Purpose:

- Preprocessor directives
- Inclusion of legacy headers

Characteristics:

- Optional section
- Appears at the beginning of the module

Example uses:

- `#include`
- Macro definitions
- Other preprocessing directives

---

## 2. Module Preamble

Purpose:

- Declares the module name
- Imports other modules

Responsibilities:

- Identifies the module
- Specifies module dependencies

---

## 3. Module Purview

Purpose:

- Contains the actual module code

Contents may include:

- Exported declarations
- Non-exported declarations
- Implementations

Exportable entities include:

- Functions
- Classes
- Namespaces
- Other C++ entities

### Exported Code

Visible to code that imports the module.

### Non-Exported Code

Internal to the module and inaccessible from outside.

---

## 4. Module Private Section (Optional)

Purpose:

- Contains implementation details that should remain hidden from users of the module

Characteristics:

- Optional section
- Used to improve encapsulation
- Helps separate public interfaces from private implementation code

---

# Module Layout Overview

```text
+----------------------------------+
| Global Module Fragment (Optional)|
+----------------------------------+
| Module Preamble                  |
| - Module Name                    |
| - Module Imports                 |
+----------------------------------+
| Module Purview                   |
| - Exported Code                  |
| - Internal Code                  |
+----------------------------------+
| Module Private Section(Optional) |
+----------------------------------+
```

---

# Key Takeaways

- Modules are a C++20 feature for organizing and sharing code.
- They address many limitations of traditional headers.
- Modules are compiled separately and imported when needed.
- They improve encapsulation and dependency management.
- They can significantly reduce compilation times.
- Not all code must be exported.
- Modules support private implementation details.
- Header files remain relevant and are not completely replaced by modules.

---

# Quick Revision

### Why were modules introduced?

To solve problems such as:

- Repeated header inclusion
- Long compilation times
- Macro leakage
- Dependency complexity

### Main advantages

- Faster builds
- Better encapsulation
- Explicit exports
- Cleaner dependency management

### Can modules replace headers completely?

No. Header files are still important and continue to be used alongside modules.

### What are the four major sections of a module?

1. Global Module Fragment (optional)
2. Module Preamble
3. Module Purview
4. Module Private Section (optional)


# C++23 Modules - A More detailed Revision.

## Overview

C++ Modules are a modern replacement for the traditional header/include system.

Traditional C++ uses:

```cpp
#include "myheader.h"
```

During compilation, the preprocessor copies the entire header content into every translation unit, causing:

- Long build times
- Repeated parsing
- Macro pollution
- Complex dependency management

Modules solve these issues by providing:

- Faster compilation
- Better encapsulation
- Clear dependency structure
- Reduced rebuild times
- Elimination of most header-related problems

---

# Traditional Header Model

Example:

```cpp
// math.h
int add(int a, int b);
```

```cpp
// math.cpp
#include "math.h"

int add(int a, int b)
{
    return a + b;
}
```

```cpp
// main.cpp
#include "math.h"

int main()
{
    return add(2, 3);
}
```

Problem:

Every source file including `math.h` must parse it repeatedly.

---

# Module Basics

Modules introduce new keywords:

```cpp
export module math;
```

and

```cpp
import math;
```

instead of:

```cpp
#include "math.h"
```

---

# Simple Module Example

## Step 1: Create Module Interface

File:

```cpp
math.cppm
```

```cpp
export module math;

export int add(int a, int b)
{
    return a + b;
}
```

Explanation:

```cpp
export module math;
```

Defines a module named `math`.

```cpp
export int add(...)
```

Exports the function so other files can use it.

---

## Step 2: Use the Module

File:

```cpp
main.cpp
```

```cpp
import math;
#include <iostream>

int main()
{
    std::cout << add(5, 3) << std::endl;
}
```

Output:

```text
8
```

---

# Separating Interface and Implementation

Large projects generally separate them.

## Interface File

```cpp
math.cppm
```

```cpp
export module math;

export int add(int a, int b);
export int sub(int a, int b);
```

---

## Implementation File

```cpp
math.cpp
```

```cpp
module math;

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}
```

Notice:

```cpp
module math;
```

No `export` here.

This is implementation-only code.

---

# Exported vs Non-Exported Symbols

Example:

```cpp
export module math;

export int add(int a, int b);

int helper(int x)
{
    return x * 2;
}
```

Only:

```cpp
add()
```

is visible outside.

`helper()` remains private to the module.

---

# Module Build Process

Unlike headers, modules are compiled first into a binary representation.

Typical flow:

```text
math.cppm
     |
     V
Compile Interface
     |
     V
BMI / IFC File
(Binary Module Interface)
     |
     +----> Used by main.cpp
     |
     +----> Used by other files
```

---

# Detailed Build Pipeline

## Phase 1

Compile Module Interface

```text
math.cppm
    |
    V
BMI / IFC
```

Generated artifacts:

- BMI
- IFC
- PCM

Compiler-specific names:

| Compiler | Artifact |
|-----------|-----------|
| GCC | BMI |
| Clang | PCM |
| MSVC | IFC |

---

## Phase 2

Compile Implementation

```text
math.cpp
    |
    V
math.o
```

Implementation uses the module definition created in Phase 1.

---

## Phase 3

Compile Consumer Code

```text
main.cpp
    |
    V
main.o
```

When compiler sees:

```cpp
import math;
```

It loads BMI/PCM/IFC rather than parsing source files.

---

## Phase 4

Link

```text
main.o
math.o
     |
     V
Executable
```

---

# Visual Build Diagram

```text
           +----------------+
           |  math.cppm     |
           | Interface      |
           +----------------+
                    |
                    V
           +----------------+
           | BMI / PCM /IFC |
           +----------------+
                    |
      +-------------+-------------+
      |                           |
      V                           V

+-------------+          +---------------+
| math.cpp    |          |  main.cpp     |
| Impl        |          | import math   |
+-------------+          +---------------+
      |                           |
      V                           V
+-------------+          +---------------+
| math.o      |          | main.o        |
+-------------+          +---------------+
           \               /
            \             /
             \           /
              V         V

              Executable
```

---

# Example Build Commands

## GCC (Experimental)

```bash
g++ -std=c++23 -fmodules-ts -c math.cppm
g++ -std=c++23 -fmodules-ts -c math.cpp
g++ -std=c++23 -fmodules-ts -c main.cpp
g++ math.o main.o -o app
```

---

## Clang

```bash
clang++ -std=c++23 \
    --precompile math.cppm \
    -o math.pcm

clang++ -std=c++23 \
    -c math.cpp

clang++ -std=c++23 \
    -fmodule-file=math=math.pcm \
    main.cpp \
    math.cpp \
    -o app
```

---

## MSVC

```bash
cl /std:c++latest math.cppm
cl /std:c++latest math.cpp
cl /std:c++latest main.cpp
```

Visual Studio handles most module dependencies automatically.

---

# Module Partitions

For large projects:

```cpp
export module math;

export import :algebra;
export import :geometry;
```

Partition:

```cpp
export module math:algebra;
```

Partition:

```cpp
export module math:geometry;
```

Benefits:

- Large codebases become manageable
- Team-level ownership
- Reduced compile dependencies

---

# Header Units

Existing headers can be imported.

Instead of:

```cpp
#include <vector>
```

Use:

```cpp
import <vector>;
```

Advantages:

- Faster compilation
- Reusable compiled form

---

# Why Modules Improve Build Time

Headers:

```text
main.cpp
 ↓
Parse vector
 ↓
Parse string
 ↓
Parse iostream
 ↓
Every build
```

Modules:

```text
Build Once
 ↓
Store BMI
 ↓
Reuse BMI
 ↓
No Reparse
```

Result:

- Faster incremental builds
- Better scalability
- Lower memory consumption

---

# Common Interview Questions

## What problem do modules solve?

Answer:

- Repeated header parsing
- Slow compilation
- Macro leakage
- Dependency complexity

---

## Difference between include and import?

Include:

```cpp
#include "math.h"
```

Preprocessor text substitution.

Import:

```cpp
import math;
```

Loads compiled module metadata.

---

## What is BMI?

BMI = Binary Module Interface.

Contains compiled information about exported module declarations.

Equivalent role:

```text
Header
   =>
BMI
```

but in binary form.

---

## Can modules replace all headers?

Not immediately.

Most real projects use:

- Legacy headers
- Third-party libraries
- Modules

together during migration.

---

# Key Takeaways

1. Modules replace much of the header/include model.
2. `export module` declares a module.
3. `import` consumes a module.
4. BMI/PCM/IFC files store compiled interface metadata.
5. Modules reduce recompilation and improve build speed.
6. Implementation can be separated from interface.
7. C++23 provides mature module support compared with earlier standards.
8. Large projects benefit significantly from module architecture.
