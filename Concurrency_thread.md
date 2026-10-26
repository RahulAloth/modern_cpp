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
