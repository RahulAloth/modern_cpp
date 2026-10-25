# C++ Coroutines

## What is a Subroutine?

A subroutine is a traditional function.

### Characteristics
- Executes when called by another function.
- Stores execution information in a **stack frame**.
- Stack frame contains:
  - Function arguments
  - Return address
  - Local variables
  - Other execution-related data
- Runs from start to finish without interruption.
- Returns control to the caller when completed.
- Stack frame is destroyed after return.

### Execution Flow

Caller Function
    ↓
Function Starts
    ↓
Execute Statements
    ↓
Function Completes
    ↓
Return Control
    ↓
Stack Frame Destroyed

### Limitation
Once a function returns:
- Execution state is lost.
- Cannot resume from where it stopped.
- Must start again from the beginning.

---

# What is a Coroutine?

A coroutine is a special function that can:

1. Suspend execution.
2. Return control to the caller.
3. Preserve its execution state.
4. Resume later from the suspension point.

### Key Difference

| Regular Function | Coroutine |
|------------------|------------|
| Runs to completion | Can pause execution |
| State stored on stack | State stored in coroutine frame |
| Stack frame destroyed on return | Coroutine frame survives suspension |
| Cannot resume | Can resume later |
| Blocking behavior | Non-blocking behavior |

---

# Coroutine Frame

A coroutine preserves its state inside a **coroutine frame**.

### Contains
- Local variables
- Current execution point
- Awaitable objects
- Promise object
- Other coroutine state

### Storage Location

In C++ coroutines, the coroutine frame is typically stored on the:

**Heap**

Reason:
- Stack memory disappears when a function returns.
- Heap memory can outlive function returns.
- Allows execution to continue later.

### Stackless Coroutines

C++ coroutines are called **stackless** because:

- Execution state is not preserved using the call stack.
- Suspension information is stored in a heap-allocated coroutine frame.

---

# Why Use Coroutines?


## Problem with Traditional Functions

A normal function blocks its caller until it finishes.

### Example

```cpp
downloadFile();   // Caller waits here
processFile();
```

### While Waiting

- User input cannot be processed.
- Other tasks cannot run.
- Application responsiveness suffers.

---

## Coroutine Solution

A coroutine can:

1. Start an operation.
2. Suspend itself.
3. Return control immediately.
4. Allow the caller to continue useful work.
5. Resume later when ready.

### Benefits

- Non-blocking execution
- Improved responsiveness
- Efficient asynchronous programming
- Better readability than callback-based code
- Lower overhead than threads in many scenarios

---

## Example Flow

Coroutine Starts
↓
Execute
↓
Suspend (co_yield / co_await)
↓
Return Control to Caller
↓
Caller Continues Working
↓
Resume Coroutine
↓
Continue from Suspension Point
↓
Finish (co_return)
## Another Example :

# Lazy Number Generation with C++23 Coroutines (`std::generator`)

## Motivation

Sometimes we need a sequence of numbers, but we do not want to create the entire sequence at once.

Earlier approaches such as `std::ranges::iota_view` or `std::views::iota` can provide a sequence of numbers, but when thinking in terms of traditional functions, we may still end up generating values eagerly.

The goal is to generate values **only when the caller requests them**, which is known as **lazy generation**.

---

# Attempt 1: Traditional Function

A simple approach is to write a function that loops through numbers and prints them.

```cpp
void numbers()
{
    for (int i = 0; i <= 10; ++i)
    {
        std::cout << i << '\n';
    }
}
```

### Problem

- All numbers are produced immediately.
- Values are printed directly.
- The caller cannot retrieve one value at a time.
- No lazy behavior exists.

---

# Attempt 2: Static State

Another approach is to return a single value per function call.

```cpp
int numbers()
{
    static int value = 1;
    return value++;
}
```

Usage:

```cpp
std::cout << numbers() << '\n';
std::cout << numbers() << '\n';
std::cout << numbers() << '\n';
```

### Advantage

- Values are generated on demand.
- Each call returns the next number.

### Problems

- Relies on a local `static` variable.
- State is shared globally within the application.
- Difficult to reset or create multiple independent sequences.
- Not a scalable solution.

---

# Coroutines Solution

C++23 introduces `std::generator`, which makes lazy sequence generation straightforward.

Include:

```cpp
#include <generator>
```

Create a coroutine:

```cpp
std::generator<int> coNumbers()
{
    for (int i = 0; i <= 10; ++i)
    {
        co_yield i;
    }
}
```

---

# Understanding `co_yield`

The statement:

```cpp
co_yield i;
```

does two things:

1. Suspends the coroutine.
2. Returns the current value to the caller.

When the caller requests the next value, execution resumes from where it previously stopped.

This enables true lazy generation.

---

# Using the Generator

A generator behaves similarly to a range.

Because it supports iterators, it can be used with range-based loops.

```cpp
for (auto value : coNumbers())
{
    std::cout << value << '\n';
}
```

Benefits:

- Familiar syntax.
- Values are produced only when needed.
- No manual state management.

---

# Custom Range Generator

A coroutine generator can easily be extended to support custom ranges.

```cpp
std::generator<int> coNumbers(int start,
                              int end,
                              int step = 1)
{
    for (int i = start; i <= end; i += step)
    {
        co_yield i;
    }
}
```

Usage:

```cpp
for (auto value : coNumbers(10, 20, 2))
{
    std::cout << value << ' ';
}
```

Output:

```text
10 12 14 16 18 20
```

---

# Why `std::generator` Is Useful

`std::generator` hides most of the coroutine infrastructure, including:

- Coroutine frame management
- Suspension and resumption logic
- Iterator implementation
- Promise type handling
- State preservation between yields

This allows developers to focus on the sequence logic rather than low-level coroutine details.

---

# Key Takeaways

- Traditional functions generate values eagerly.
- Static-variable solutions provide laziness but introduce shared state.
- C++23 `std::generator` provides clean lazy sequence generation.
- `co_yield` pauses execution and returns a value.
- Generators behave like ranges and support iteration.
- Custom start, end, and step values can be implemented easily.
- `std::generator` hides the underlying coroutine machinery while exposing a simple interface.

---

# Concept Summary

```text
Traditional Function
    ↓
Generates everything immediately

Static Variable Function
    ↓
Generates lazily but shares state

Coroutine + std::generator
    ↓
Generates lazily
Maintains independent state
Supports iteration
Clean and scalable solution
```

# Understanding Coroutine Components in C++

## Overview

A coroutine consists of two main parts:

1. A **coroutine function** that contains coroutine keywords.
2. A **coroutine type** that acts as the interface exposed to the caller.

Understanding these components is essential before implementing a custom coroutine type.

---

# Coroutine Function

Consider a coroutine type named `task`.

```cpp
task coFunction()
{
    co_return;
}
```

Because the function contains a coroutine keyword (`co_return`), it becomes a coroutine.

A coroutine may contain any of the following keywords:

```cpp
co_return
co_yield
co_await
```

### Rule

If a function contains at least one of these keywords, the compiler treats it as a coroutine.

---

# Coroutine Invocation

When a coroutine function is called:

```cpp
auto result = coFunction();
```

the function returns an object of the coroutine type.

```cpp
task
```

This returned object becomes the interface through which the caller interacts with the coroutine.

---

# Coroutine Type

The coroutine type represents the public API of the coroutine.

Example:

```cpp
task
```

or

```cpp
std::generator<int>
```

The caller typically interacts only with this type and not with the internal coroutine machinery.

---

# Example: `std::generator`

In previous examples we used:

```cpp
std::generator<int>
```

`std::generator` is a coroutine type provided by the standard library.

It exposes a clean range-like interface while hiding the implementation details of coroutines.

---

# Internal Structure of a Coroutine Type

Conceptually, a coroutine type contains several important components.

```text
Coroutine Type (task / generator)
│
├── Coroutine Handle
├── Coroutine Frame
└── promise_type
```

---

# 1. Coroutine Handle

The coroutine handle provides a way to reference and control a coroutine.

Conceptually it allows operations such as:

- Resuming execution
- Suspending execution
- Destroying the coroutine
- Accessing coroutine state

```cpp
std::coroutine_handle<>
```

Think of the handle as a lightweight object that points to the actual coroutine.

---

# 2. Coroutine Frame

The coroutine frame stores all state required by the coroutine.

Examples include:

- Local variables
- Function parameters
- Suspension points
- Return values
- Awaitable state

```text
Coroutine Frame
├── Local Variables
├── Parameters
├── Current Execution State
└── Suspension Information
```

### Important

The coroutine frame is typically allocated on the heap.

This allows the coroutine state to survive after a function suspension.

---

# Relationship Between Handle and Frame

```text
Coroutine Handle
       │
       ▼
Coroutine Frame
       │
       ▼
Stored Coroutine State
```

The handle essentially points to and manages the coroutine frame.

---

# 3. `promise_type`

Every custom coroutine type must provide a nested class named:

```cpp
promise_type
```

Example:

```cpp
struct task
{
    struct promise_type
    {
    };
};
```

### Important

The name must be exactly:

```cpp
promise_type
```

The compiler searches for this specific nested type when building coroutine support.

---

# Purpose of `promise_type`

`promise_type` defines how the coroutine communicates with its coroutine type.

It acts as the customization point for coroutine behavior.

Responsibilities may include:

- Creating the coroutine object
- Returning values
- Handling exceptions
- Determining suspension behavior
- Managing coroutine lifecycle

---

# Conceptual Relationship

```text
Coroutine Function
        │
        ▼
Creates Coroutine Frame
        │
        ▼
Uses promise_type
        │
        ▼
Returns Coroutine Type (task)
        │
        ▼
Used By Caller
```

---

# What the Caller Sees

The caller only interacts with:

```cpp
task
```

or

```cpp
std::generator<int>
```

The following implementation details remain hidden:

- Coroutine frame
- Coroutine handle
- `promise_type`
- Suspension machinery
- Compiler-generated state machine

---

# Minimal Skeleton of a Custom Coroutine Type

```cpp
struct task
{
    struct promise_type
    {
        // Coroutine customization points
    };
};
```

This nested `promise_type` is the first requirement when implementing a custom coroutine type.

---

# Key Takeaways

- A function becomes a coroutine when it contains `co_return`, `co_yield`, or `co_await`.
- Calling a coroutine returns a coroutine type object.
- The coroutine type acts as the public API.
- A coroutine internally uses a coroutine handle for control and access.
- The coroutine frame stores the execution state of the coroutine.
- The coroutine frame typically lives on the heap.
- Every custom coroutine type must define a nested class named `promise_type`.
- `promise_type` provides the customization mechanisms that control coroutine behavior.
- Standard types such as `std::generator` already implement all these components for us.

---

# Mental Model

```text
coFunction()
      │
      ▼
Creates Coroutine Frame
      │
      ▼
Managed by Coroutine Handle
      │
      ▼
Configured by promise_type
      │
      ▼
Exposed as Coroutine Type (task)
      │
      ▼
Used by Caller
```

# Building a Custom Coroutine Type in C++

## Goal

To create a custom coroutine type, we must define a class that represents the coroutine API exposed to the caller.

In this example, the coroutine type is called:

```cpp
task
```

The caller interacts only with the `task` object, while all coroutine machinery remains hidden internally.

---

# Step 1: Include Coroutine Support

```cpp
#include <coroutine>
```

This header provides:

- `std::coroutine_handle`
- `std::suspend_always`
- `std::suspend_never`
- Coroutine infrastructure used by the compiler

---

# Step 2: Define the Coroutine Type

```cpp
class task
{
public:
    struct promise_type
    {
        // Required coroutine functions
    };

private:
    // Internal coroutine state
};
```

### Important

Every coroutine type must expose a nested type named exactly:

```cpp
promise_type
```

The compiler looks for this specific name when transforming a function into a coroutine.

---

# Alternative Organization

The implementation can be separated if desired.

```cpp
struct my_promise
{
    // implementation
};

class task
{
public:
    using promise_type = my_promise;
};
```

The compiler only requires that `task::promise_type` exists.

---

# Required Functions in `promise_type`

A minimal coroutine type requires several member functions.

```cpp
struct promise_type
{
    task get_return_object();

    std::suspend_always initial_suspend();

    std::suspend_always final_suspend() noexcept;

    void unhandled_exception();

    void return_void();
};
```

---

# Purpose of Each Function

## `get_return_object()`

Creates the coroutine object returned to the caller.

```cpp
task get_return_object();
```

This function is called by the coroutine runtime during coroutine creation.

---

## `initial_suspend()`

Determines what happens immediately after the coroutine is created.

```cpp
std::suspend_always initial_suspend();
```

If it returns:

```cpp
std::suspend_always{}
```

the coroutine pauses before executing its body.

---

## `final_suspend()`

Executed when the coroutine reaches completion.

```cpp
std::suspend_always final_suspend() noexcept;
```

This defines the coroutine's final suspension behavior.

---

## `return_void()`

Called when:

```cpp
co_return;
```

is executed.

```cpp
void return_void();
```

Used for coroutines that do not return a value.

---

## `unhandled_exception()`

Invoked if an exception escapes the coroutine.

```cpp
void unhandled_exception();
```

A minimal implementation may leave it empty initially.

---

# Runtime Sequence During Coroutine Creation

When the coroutine function is called:

```cpp
coFunction();
```

the runtime performs roughly the following steps:

```text
Create Promise Object
        ↓
Call get_return_object()
        ↓
Create task Object
        ↓
Create Coroutine Handle
        ↓
Call initial_suspend()
        ↓
Return Control To Caller
```

---

# Storing the Coroutine Handle

The coroutine type usually owns a handle.

```cpp
std::coroutine_handle<promise_type> handle_;
```

Example:

```cpp
class task
{
public:
    struct promise_type;

private:
    std::coroutine_handle<promise_type> handle_;
};
```

---

# Creating the Handle

The promise object can be converted into a coroutine handle using:

```cpp
std::coroutine_handle<promise_type>::from_promise(*this)
```

Inside `get_return_object()`:

```cpp
task promise_type::get_return_object()
{
    return task{
        std::coroutine_handle<promise_type>::from_promise(*this)
    };
}
```

---

# Constructor for `task`

The handle is passed into the coroutine object.

```cpp
task(std::coroutine_handle<promise_type> handle)
    : handle_(handle)
{
}
```

This links the returned `task` object to the actual coroutine.

---

# Creating a Coroutine Function

```cpp
task coFunction()
{
    co_return;
}
```

Since it contains:

```cpp
co_return
```

the compiler transforms it into a coroutine.

---

# Invoking the Coroutine

```cpp
auto t = coFunction();
```

The returned object:

```cpp
t
```

contains the coroutine handle.

This object becomes the interface used to control the coroutine.

---

# Common Compilation Issue

If `promise_type` is declared in a private section:

```cpp
class task
{
private:
    struct promise_type;
};
```

the compiler cannot locate it.

Result:

```text
promise_type is not a member of coroutine traits
```

### Fix

Make it public.

```cpp
class task
{
public:
    struct promise_type;
};
```

---

# Understanding Initial Suspension

Suppose:

```cpp
std::suspend_always initial_suspend()
{
    return {};
}
```

When the coroutine is created:

```cpp
auto t = coFunction();
```

execution stops before entering the function body.

Flow:

```text
Coroutine Created
        ↓
initial_suspend()
        ↓
Suspend
        ↓
Return To Caller
```

Therefore, statements inside the coroutine have not yet executed.

---

# Why the Coroutine Body Doesn't Run

Consider:

```cpp
task coFunction()
{
    std::cout << "Inside coroutine\n";

    co_return;
}
```

Calling:

```cpp
auto t = coFunction();
```

does not print anything yet.

Reason:

```cpp
initial_suspend()
```

paused execution before reaching the first statement.

---

# Resuming the Coroutine

The handle can be resumed manually.

A helper function can be added:

```cpp
void resume()
{
    if (handle_)
    {
        handle_.resume();
    }
}
```

Usage:

```cpp
auto t = coFunction();

t.resume();
```

---

# Execution Flow After Resume

Calling:

```cpp
t.resume();
```

continues execution inside the coroutine.

```text
Resume
   ↓
Execute Coroutine Body
   ↓
Reach co_return
   ↓
return_void()
   ↓
final_suspend()
```

---

# What Happens at `co_return`

For:

```cpp
co_return;
```

the runtime calls:

```cpp
return_void();
```

This acts as the completion point for a void-returning coroutine.

---

# Final Suspension

After `return_void()`:

```cpp
final_suspend()
```

is executed.

If it returns:

```cpp
std::suspend_always{}
```

the coroutine suspends once more before destruction.

```text
Coroutine Body Ends
         ↓
return_void()
         ↓
final_suspend()
         ↓
Suspend Again
```

This gives an opportunity to:

- Inspect state
- Perform cleanup
- Transfer ownership
- Schedule destruction later

---

# Complete Lifecycle

```text
coFunction()
      ↓
Create Promise Object
      ↓
get_return_object()
      ↓
Create task Object
      ↓
Create Coroutine Handle
      ↓
initial_suspend()
      ↓
Suspend
      ↓
Caller Receives task
      ↓
resume()
      ↓
Execute Coroutine Body
      ↓
co_return
      ↓
return_void()
      ↓
final_suspend()
      ↓
Suspend
      ↓
Destroy Coroutine
```

---

# Key Takeaways

- A custom coroutine type must define a nested `promise_type`.
- `promise_type` must be publicly accessible.
- `get_return_object()` creates the coroutine API object.
- `std::coroutine_handle` is used to control the coroutine.
- `initial_suspend()` controls startup behavior.
- Returning `std::suspend_always` pauses execution immediately.
- `resume()` is required to continue execution.
- `co_return` invokes `return_void()` for void coroutines.
- `final_suspend()` controls behavior after the coroutine finishes.
- The `task` object acts as the public interface while the coroutine machinery remains hidden.

---

# Mental Model

```text
Caller
  │
  ▼
task Object
  │
  ▼
Coroutine Handle
  │
  ▼
Coroutine Frame
  │
  ├── promise_type
  ├── Local Variables
  ├── Execution State
  └── Suspension State
```

# Coroutine Lifecycle, Suspension Behavior, and Memory Management

## Goal

After building a basic custom coroutine type, it is important to understand:

- How `promise_type` is created and destroyed
- How coroutine suspension works
- How memory is managed
- When `resume()` is safe to call
- The difference between `suspend_always` and `suspend_never`

Understanding these concepts helps prevent crashes and memory leaks.

---

# Tracking Object Creation

To observe the coroutine lifecycle, logging can be added to constructors and destructors.

Example:

```cpp
promise_type()
{
    LOG("promise_type()");
}

~promise_type()
{
    LOG("~promise_type()");
}
```

Similarly:

```cpp
task(std::coroutine_handle<promise_type> h)
    : handle_(h)
{
    LOG("task()");
}

~task()
{
    LOG("~task()");
}
```

These logs help visualize the order in which coroutine-related objects are created and destroyed during execution.

---

# Observing the Coroutine Lifecycle

Consider the following code:

```cpp
auto t = coFunction();

t.resume();

LOG("End of main");
```

When the coroutine is invoked, the runtime performs several operations automatically.

Execution flow:

```text
Call coFunction()
        ↓
Construct promise_type
        ↓
Call get_return_object()
        ↓
Construct task
        ↓
Call initial_suspend()
        ↓
Suspend Coroutine
        ↓
Return task Object To Caller
        ↓
Caller Calls resume()
        ↓
Execute Coroutine Body
        ↓
Execute co_return
        ↓
Call return_void()
        ↓
Call final_suspend()
        ↓
Suspend Again
        ↓
End Of Main
        ↓
Destroy task
```

Typical output:

```text
promise_type()
get_return_object()
task()
initial_suspend()

resume()

coFunction()

return_void()
final_suspend()

End of main

~task()
```

---

# Missing Destructor Call

Notice something important:

```text
~promise_type()
```

never appears.

This means the promise object was never destroyed.

Since the promise object lives inside the coroutine frame, the coroutine frame itself was not released.

Result:

```text
Memory Leak
```

---

# Why the Leak Happens

The coroutine frame is allocated dynamically by the runtime.

Conceptually:

```text
Coroutine Handle
        │
        ▼
Coroutine Frame
        ├── promise_type
        ├── Local Variables
        └── Coroutine State
```

Destroying only the `task` object does not automatically destroy the coroutine frame.

The frame must be explicitly released.

---

# Fixing the Memory Leak

The coroutine handle provides:

```cpp
destroy()
```

which destroys the coroutine frame and all associated objects.

Example:

```cpp
~task()
{
    if (handle_)
    {
        handle_.destroy();
    }
}
```

Now the output becomes:

```text
~task()
~promise_type()
```

confirming proper cleanup.
