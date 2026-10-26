# Introduction to C++ Concurrency and Threads

---

# 1. What is Concurrency?

Concurrency is a property of an application where multiple operations can execute independently and make progress during the same period of time.

Large software systems often contain many components that need to perform different tasks simultaneously, such as:

- User interface processing
- File downloads
- Network communication
- Database access
- Sensor data acquisition
- Background computations

Concurrency enables:

- Better CPU utilization
- Improved application responsiveness
- Separation of long-running work from user interactions
- Better user experience

---

# 2. C++11 and Concurrency

Starting from **C++11**, the language provides built-in support for concurrency.

The standard library includes:

- Thread creation (`std::thread`)
- Synchronization primitives
- Mutexes
- Condition variables
- Atomic operations
- Thread management utilities

This allows developers to create and manage multiple threads directly within their applications.

---

# 3. The Single-Threaded Problem

Consider a function that performs an expensive operation such as downloading a file.

### Example

```cpp
#include <iostream>
#include <list>

std::list<int> data;

void Download()
{
    for (int i = 0; i < 100000000; i++)
    {
        data.push_back(i);
    }

    std::cout << "Download finished\n";
}

int main()
{
    std::cout << "User started an operation\n";

    Download();

    std::cout << "User started another operation\n";
}
```

### Execution Flow

```text
Main Thread
    |
    +--> Print "User started an operation"
    |
    +--> Execute Download()
             |
             +--> Long running work
             |
             +--> Finish
    |
    +--> Print "User started another operation"
```

---

# 4. Why Does the Program Pause?

The `Download()` function executes on the same thread as `main()`.

Since only one thread is available:

1. `main()` calls `Download()`
2. Control moves into `Download()`
3. The thread remains busy
4. `main()` cannot continue
5. The next statement executes only after `Download()` completes

Result:

```text
Main thread is blocked.
```

---

# 5. The Main (Primary) Thread

Every application starts with one thread called:

- Main Thread
- Primary Thread

This thread is responsible for:

- Running program logic
- Processing events
- Handling user input
- Updating UI elements
- Dispatching callbacks

A simplified view:

```text
Application
    |
    +--> Main Thread
            |
            +--> User Input
            +--> UI Updates
            +--> Business Logic
```

When the main thread becomes busy:

```text
User Input -> Waiting
UI Updates -> Waiting
Program Logic -> Busy
```

The application appears frozen.

---

# 6. UI Application Example

A GUI application built with Qt contains:

```text
[ Push Button ]
[ Other Controls ]
```

When a user presses a button:

```cpp
void MainWindow::on_pushButton_clicked()
{
    // Callback code
}
```

Normally:

```text
Button Click
      |
      +--> Callback
      |
      +--> Message Box
```

Everything remains responsive because execution finishes quickly.

---

# 7. What Happens with a Long Operation in the UI Thread?

Suppose the download code is moved into the button-click callback.

```cpp
void MainWindow::on_pushButton_clicked()
{
    for (...)
    {
        data.push_back(...);
    }

    QMessageBox::information(...);
}
```

Execution becomes:

```text
Button Click
      |
      +--> Long Running Download
                |
                | (UI blocked)
                |
                V
        Download Finishes
                |
                V
        Show Message Box
```

During the download:

- Buttons do not respond
- Window cannot be interacted with
- Menus stop responding
- User sees "Not Responding"

---

# 8. Why the Application Freezes

The UI framework relies on an event loop.

```text
Main Thread
     |
     +--> Event Loop
              |
              +--> Mouse Events
              +--> Keyboard Events
              +--> Paint Events
              +--> Button Clicks
```

When a long-running task occupies the thread:

```text
Event Loop
      |
      X Cannot Process Events
```

Consequences:

- No mouse handling
- No keyboard handling
- No screen updates
- Window appears frozen

---

# 9. User Experience Impact

If background work is executed on the main thread:

### Problems

- Application feels slow
- UI stops responding
- Users think the application crashed
- Operating system may mark it as "Not Responding"

### Result

Poor user experience.

---

# 10. Solution: Use a Separate Thread

Long-running operations should execute in a worker thread.

Conceptually:

```text
Main Thread
    |
    +--> User Interface
    +--> Event Handling

Worker Thread
    |
    +--> File Download
    +--> Network Requests
    +--> Heavy Computation
```

Benefits:

- UI remains responsive
- User can continue interacting
- Better resource utilization
- Improved application performance

---

# 11. Key Takeaways

### Concurrency

- Allows multiple operations to make progress simultaneously.

### C++11

- Introduced standard threading support.

### Main Thread

- Handles program execution and user interactions.

### Problem

- Long-running work blocks the main thread.

### GUI Impact

- Interface becomes unresponsive.
- Users may see "Not Responding".

### Best Practice

✅ Keep the UI thread free for user interaction.

✅ Move expensive work to worker threads.

✅ Use `std::thread` or higher-level concurrency mechanisms.

---

# Memory Aid

```text
Main Thread Rule:

Fast Work      -> Main Thread ✅
Heavy Work     -> Worker Thread ✅

Heavy Work     -> Main Thread ❌
```

Or simply:

"Never block the UI thread."

# Joinable Threads and Detached Threads

---

# 1. Creating Threads in C++11

C++11 introduced the `<thread>` library which allows programs to execute multiple tasks concurrently.

The central class is:

```cpp
std::thread
```

This class represents a thread of execution.

---

# 2. What is a Callable?

The `std::thread` constructor accepts a **callable object**.

A callable is anything that can be invoked like a function.

Examples:

### Function Pointer

```cpp
void Download();

std::thread t(Download);
```

### Function Object (Functor)

```cpp
struct Downloader
{
    void operator()()
    {
        // work
    }
};

std::thread t(Downloader());
```

### Lambda Function

```cpp
std::thread t([]()
{
    std::cout << "Hello";
});
```

---

# 3. How std::thread Works

When a thread object is created:

```cpp
std::thread t(Download);
```

the following happens:

```text
Main Thread
     |
     +--> Creates Child Thread
                |
                +--> Executes Download()
```

Important:

✅ Thread creation is non-blocking.

The constructor returns immediately.

```text
Create Thread
      |
      +--> Child Thread Starts
      |
      +--> Main Continues
```

The main thread does not wait for the child thread to begin execution.

---

# 4. Basic Example

```cpp
#include <iostream>
#include <thread>

void Download()
{
    std::cout << "Downloading...\n";
}

int main()
{
    std::thread t(Download);

    t.join();
}
```

---

# 5. Two Threads are Now Running

After creating the thread:

```cpp
std::thread t(Download);
```

there are now two independent execution paths:

```text
Process
│
├── Main Thread
│
└── Child Thread
      │
      └── Download()
```

Both threads execute concurrently.

---

# 6. The Problem if Main Exits Early

Consider:

```cpp
int main()
{
    std::thread t(Download);

    return 0;
}
```

Possible execution:

```text
Main Thread
     |
     +--> Creates Child Thread
     |
     +--> Returns
     |
     +--> Process Terminates

Child Thread
     |
     +--> Did not finish
```

When `main()` returns:

```text
Exit Process
```

is called.

This terminates the process and all threads inside it.

The child thread may never complete.

---

# 7. Joinable Threads

By default every newly created thread is:

```text
JOINABLE
```

Example:

```cpp
std::thread t(Download);
```

creates a joinable thread.

A joinable thread expects someone to wait for its completion.

---

# 8. Joining a Thread

Use:

```cpp
t.join();
```

Example:

```cpp
std::thread t(Download);

t.join();
```

Execution:

```text
Main Thread
     |
     +--> Create Child
     |
     +--> Wait at join()
                |
                +--> Child finishes
                |
                +--> Main resumes
```

---

# 9. What Does join() Do?

`join()` performs two tasks:

### 1. Waits for Completion

```text
Main Thread BLOCKS
```

until the child thread finishes.

### 2. Reclaims Thread Resources

Operating system resources used by the thread are released safely.

---

# 10. Why join() is Mandatory

Consider:

```cpp
void func()
{
    std::thread t(Download);

}   // thread object destroyed here
```

When the thread object leaves scope:

```cpp
~thread()
```

is invoked.

If the thread is still joinable:

```text
std::terminate()
```

is called.

Program crashes immediately.

---

# 11. Critical Rule

Always do one of the following before destruction:

```cpp
t.join();
```

or

```cpp
t.detach();
```

Never leave a joinable thread unmanaged.

---

# 12. Visualizing a Joinable Thread

```text
Main Thread
     |
     +--> std::thread t(...)
     |
     +--> t.join()
             |
             +--> Wait
                     |
                     +--> Child finishes
             |
             +--> Continue
```

---

# 13. Detached Threads

Sometimes a task should continue in the background.

Examples:

- Logging
- File monitoring
- Telemetry
- Background cleanup
- Analytics

In such situations we may not want to wait.

Use:

```cpp
t.detach();
```

Example:

```cpp
std::thread t(Download);

t.detach();
```

---

# 14. What Happens After detach()?

Execution becomes:

```text
Main Thread
      |
      +--> Create Child
      |
      +--> Detach Child
      |
      +--> Continue
```

Now:

```text
Child Thread
      |
      +--> Runs Independently
```

The thread is no longer associated with the thread object.

---

# 15. Detached Thread Characteristics

### Main Thread Does Not Wait

```cpp
t.detach();
```

removes the waiting requirement.

### Child Runs Independently

```text
Main -----> exits
Child ----> may continue
```

as long as the process itself remains alive.

### Resources are Automatically Released

When the detached thread finishes:

```text
OS automatically cleans resources.
```

---

# 16. Detached Threads Cannot Be Joined

This is illegal:

```cpp
t.detach();

t.join();     // ERROR
```

After detaching:

```text
No ownership remains.
```

The thread object no longer controls the thread.

---

# 17. Checking Thread State

Use:

```cpp
t.joinable()
```

Example:

```cpp
if (t.joinable())
{
    t.join();
}
```

This prevents errors.

---

# 18. joinable() Behavior

### Before Join

```cpp
std::thread t(Download);

t.joinable();
```

returns:

```text
true
```

### Before Detach

```cpp
std::thread t(Download);

t.joinable();
```

returns:

```text
true
```

### After Join

```cpp
t.join();
```

returns:

```text
false
```

### After Detach

```cpp
t.detach();
```

returns:

```text
false
```

---

# 19. One-Way Transition

A thread can move from:

```text
Joinable
    |
    +--> Joined
```

or

```text
Joinable
    |
    +--> Detached
```

But:

```text
Detached
    |
    +--> Joinable
```

❌ Impossible

Once detached, ownership is lost permanently.

---

# 20. Why Detached Threads Need Care

Dangerous example:

```cpp
void Download()
{
    // uses global data
}

int main()
{
    std::thread t(Download);

    t.detach();

    return 0;
}
```

Execution:

```text
Main exits
Process terminates
Child thread killed
```

The detached thread may never complete.

Detaching does **not** keep the process alive.

---

# 21. Join vs Detach

| Feature | join() | detach() |
|----------|---------|---------|
| Waits for completion | ✅ Yes | ❌ No |
| Main thread blocks | ✅ Yes | ❌ No |
| Reclaims resources | ✅ Yes | ✅ Yes |
| Thread remains controlled | ✅ Yes | ❌ No |
| Can call join later | ✅ Yes | ❌ No |
| Best for important work | ✅ Yes | ❌ Risky |

---

# 22. Life Cycle of a Thread

```text
Thread Created
      |
      V
Joinable
     / \
    /   \
join() detach()
   |       |
   V       V
Joined Detached
   |       |
   +--- Resources Released ---+
```

---

# Exam / Interview Notes

### Q1: Which header provides threading support?

```cpp
#include <thread>
```

---

### Q2: What is a joinable thread?

A thread that has been created and not yet joined or detached.

---

### Q3: What happens if a joinable thread is destroyed?

```text
std::terminate() is called.
```

---

### Q4: What does join() do?

1. Waits for child thread completion.
2. Cleans up thread resources.

---

### Q5: What does detach() do?

Separates the thread from its thread object and allows it to execute independently.

---

### Q6: Can a detached thread be joined later?

```text
No.
```

---

### Q7: Can a detached thread become joinable again?

```text
No.
```

---

# Memory Aid

```text
JOIN
  = Wait For Thread

DETACH
  = Forget The Thread

JOINABLE
  = Must Handle Before Destruction
```

Most beginners should follow:

```text
Create Thread
      +
Join Thread
```

until they fully understand thread lifetimes and synchronization.
