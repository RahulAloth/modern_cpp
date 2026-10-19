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
