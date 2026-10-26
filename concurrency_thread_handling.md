# Passing Arguments to Threads in C++11

> This note focuses on how `std::thread` receives arguments, pass-by-value vs pass-by-reference, and the use of `std::ref()` and `std::cref()`.

---

# 1. Passing Arguments to Thread Functions

The constructor of `std::thread` is a **variadic constructor**.

A variadic constructor can accept:

```text
0 arguments
1 argument
2 arguments
...
N arguments
```

Format:

```cpp
std::thread thread_object(
    callable,
    arg1,
    arg2,
    arg3,
    ...
);
```

Where:

- First argument → callable
- Remaining arguments → parameters for the callable

---

# 2. Basic Example

Suppose our thread function requires a filename.

```cpp
void Download(std::string file)
{
    std::cout << file << std::endl;
}
```

Create the thread:

```cpp
std::string file = "data.zip";

std::thread t(Download, file);

t.join();
```

Internally:

```text
Thread Constructor
        |
        +--> Download(file)
```

The second argument is automatically forwarded to the thread function.

---

# 3. Visual Representation

```text
Main Thread
     |
     +--> std::thread t(Download, file)
                     |
                     V
              Child Thread
                     |
                     +--> Download(file)
```

---

# 4. Default Behavior: Pass By Value

Consider:

```cpp
std::string file = "video.mp4";

std::thread t(Download, file);
```

Thread constructor performs:

```cpp
copy(file)
```

before sending it to the child thread.

Conceptually:

```text
Original Object
       |
       +--> Copy
                 |
                 +--> Child Thread
```

---

# 5. Why Does std::thread Copy Arguments?

When a new thread starts:

```text
Main Thread
Child Thread
```

execute independently.

The thread library cannot assume that the original object will still exist.

Therefore it creates its own safe copy.

---

# 6. Demonstrating the Copy

A custom string class was created with logging.

```cpp
class String
{
public:

    String()
    {
        std::cout << "Constructor\n";
    }

    String(const String&)
    {
        std::cout << "Copy Constructor\n";
    }

    ~String()
    {
        std::cout << "Destructor\n";
    }
};
```

Thread creation:

```cpp
String s;

std::thread t(Download, s);
```

Output:

```text
Constructor
Copy Constructor
```

This proves that the thread constructor copies the object.

---

# 7. Problem With Copies

Copying may be expensive.

Examples:

```cpp
std::string
std::vector
std::map
Image Buffers
Large Data Structures
```

Unnecessary copies can:

- Waste memory
- Increase execution time
- Reduce performance

---

# 8. Passing By Reference

Suppose the thread function expects:

```cpp
void Download(String& s)
{
}
```

You might try:

```cpp
std::thread t(Download, s);
```

but this does **not** work as expected.

Why?

Because `std::thread` still performs a copy internally.

---

# 9. std::ref()

To force reference semantics use:

```cpp
std::ref()
```

Example:

```cpp
String str;

std::thread t(
    Download,
    std::ref(str)
);

t.join();
```

Now:

```text
Original Object
       |
       +--> Reference
              |
              +--> Child Thread
```

No copy occurs.

---

# 10. What std::ref() Does

`std::ref()` creates a wrapper object.

```cpp
std::reference_wrapper<T>
```

The thread library recognizes this wrapper and passes the actual object reference.

Conceptually:

```cpp
std::ref(obj)
```

means:

```text
Pass obj directly
Do not copy obj
```

---

# 11. Before vs After std::ref()

Without `std::ref()`:

```cpp
String s;

std::thread t(Download, s);
```

Output:

```text
Constructor
Copy Constructor
```

---

With `std::ref()`:

```cpp
String s;

std::thread t(
    Download,
    std::ref(s)
);
```

Output:

```text
Constructor
```

Only one object exists.

---

# 12. Constant References

In real-world applications we commonly pass objects as:

```cpp
const T&
```

Example:

```cpp
void Download(
    const String& str
);
```

For this use:

```cpp
std::cref()
```

---

# 13. Using std::cref()

Example:

```cpp
String str;

std::thread t(
    Download,
    std::cref(str)
);

t.join();
```

`cref` means:

```text
Constant Reference
```

Equivalent to:

```cpp
const String&
```

---

# 14. Difference Between ref and cref

### std::ref()

```cpp
String&
```

Allows modification.

Example:

```cpp
void Func(String& s)
{
    s.Update();
}
```

---

### std::cref()

```cpp
const String&
```

Read only.

Example:

```cpp
void Func(const String& s)
{
    s.Print();
}
```

---

# 15. Practical Example

### Copy

```cpp
std::string file = "movie.mkv";

std::thread t(
    Download,
    file
);
```

```text
Creates Copy
```

---

### Reference

```cpp
std::thread t(
    Download,
    std::ref(file)
);
```

```text
Uses Same Object
```

---

### Constant Reference

```cpp
std::thread t(
    Download,
    std::cref(file)
);
```

```text
Uses Same Object
(Read-Only)
```

---

# 16. Important Rule

Whenever a thread function accepts:

```cpp
T&
```

use:

```cpp
std::ref()
```

Whenever a thread function accepts:

```cpp
const T&
```

use:

```cpp
std::cref()
```

---

# 17. Thread Argument Flow

### Pass By Value

```text
Main Object
      |
      V
     Copy
      |
      V
Thread Function
```

---

### Pass By Reference

```text
Main Object
      |
      +-----------+
                  |
                  V
          Thread Function
```

Same object shared.

---

# 18. Returning Data From a Thread

Unlike normal functions:

```cpp
int Add()
{
    return 10;
}
```

a thread function cannot directly return data to another thread.

Example:

```cpp
void Download()
{
}
```

The return value is not captured through `std::thread`.

---

# 19. How Do Threads Send Results?

Threads typically communicate using:

### Shared Variables

```cpp
int result;
```

---

### References

```cpp
void Download(int& result)
{
}
```

---

### Mutex-Protected Data

```cpp
std::mutex
```

---

### Condition Variables

```cpp
std::condition_variable
```

---

### Promises / Futures

```cpp
std::promise
std::future
```

---

### Async Tasks

```cpp
std::async
```

The transcript hints that these mechanisms will be introduced later.

---

# Common Interview Questions

### Q1: How are arguments passed to std::thread?

By specifying them after the callable.

```cpp
std::thread t(Func, arg1, arg2);
```

---

### Q2: Are thread arguments copied by default?

✅ Yes.

---

### Q3: How do you pass by reference?

```cpp
std::ref(obj)
```

---

### Q4: How do you pass a const reference?

```cpp
std::cref(obj)
```

---

### Q5: What happens if you write?

```cpp
std::thread t(Func, obj);
```

The object is copied into thread storage.

---

### Q6: Can thread functions directly return values?

❌ No.

Alternative mechanisms such as references, promises, futures, or shared data structures must be used.

---

# Memory Aid

```text
Thread Arguments Rule

obj            -> Copy
ref(obj)       -> Reference
cref(obj)      -> Const Reference
```

or simply:

```cpp
std::thread t(Func, obj);        // copy

std::thread t(Func, std::ref(obj));   // T&

std::thread t(Func, std::cref(obj));  // const T&
```

These three patterns cover most real-world thread argument passing scenarios.

# Returning Values from Threads using std::packaged_task and std::future

- This note explains why threads cannot directly return values and how C++11 provides `std::packaged_task` and `std::future` to retrieve results from asynchronous execution.

---

# 1. The Problem: Returning Values from Threads

For a normal function:

```cpp
int Add(int x, int y)
{
    return x + y;
}
```

obtaining the result is straightforward:

```cpp
int result = Add(2, 3);

std::cout << result;
```

Output:

```text
5
```

---

# 2. What Happens with std::thread?

Suppose we execute the same function inside a thread.

```cpp
std::thread t(Add, 2, 3);
```

Problem:

```text
Where does the return value go?
```

The answer is:

```text
It is discarded.
```

`std::thread` does not provide any mechanism to capture a function's return value.

---

# 3. Why std::thread Cannot Return Values

A thread is intended only to execute work.

```text
Main Thread
      |
      +--> Create Child Thread
                  |
                  +--> Execute Function
```

The new thread runs independently.

There is no built-in channel through which:

```cpp
return result;
```

can be sent back to the creator thread.

---

# 4. Solution: std::packaged_task

C++11 introduces:

```cpp
std::packaged_task
```

Header:

```cpp
#include <future>
```

A `packaged_task` wraps a callable and connects it with a future.

---

# 5. What is a packaged_task?

Think of it as:

```text
Callable Wrapper
```

It can wrap:

- Normal functions
- Member functions
- Lambdas
- Functors (function objects)

Conceptually:

```text
Function
    |
    V
packaged_task
    |
    V
future
```

---

# 6. Creating a packaged_task

Suppose we have:

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

Create task:

```cpp
std::packaged_task<int(int,int)> task(Add);
```

Syntax:

```cpp
std::packaged_task<
        return_type(parameter_types)
>
```

---

# 7. Understanding the Signature

Function:

```cpp
int Add(int,int)
```

Signature:

```cpp
int(int,int)
```

Therefore:

```cpp
std::packaged_task<int(int,int)>
```

---

# 8. packaged_task Becomes a Proxy

After wrapping:

```cpp
std::packaged_task<int(int,int)> task(Add);
```

you can invoke:

```cpp
task(2,3);
```

instead of:

```cpp
Add(2,3);
```

Conceptually:

```text
task ---> Add
```

or

```text
Proxy ---> Real Function
```

---

# 9. Why task() Doesn't Return the Result

You may expect:

```cpp
int result = task(2,3);
```

But this is not how `packaged_task` works.

Instead:

```text
Result is stored internally
```

and must be accessed through a future.

---

# 10. Introducing std::future

A future represents:

```text
A value that will become available later.
```

Think of it as:

```text
Promise Box
```

that will eventually contain the result.

---

# 11. Creating a Future

A packaged task creates the future.

```cpp
auto future = task.get_future();
```

Example:

```cpp
std::packaged_task<int(int,int)>
    task(Add);

std::future<int> fut =
    task.get_future();
```

---

# 12. Relationship Between Task and Future

```text
packaged_task
       |
       V
     future
       |
       V
    Result
```

The two objects are connected.

---

# 13. Getting the Result

Execute:

```cpp
task(2,3);
```

Later:

```cpp
int result = fut.get();
```

Output:

```text
5
```

---

# 14. Complete Example

```cpp
#include <future>

int Add(int x, int y)
{
    return x + y;
}

int main()
{
    std::packaged_task<int(int,int)>
        task(Add);

    std::future<int> result =
        task.get_future();

    task(2,3);

    std::cout << result.get();
}
```

---

# 15. Another Example: Square

Function:

```cpp
int Square(int x)
{
    return x * x;
}
```

Task:

```cpp
std::packaged_task<int(int)>
    task(Square);
```

Future:

```cpp
auto result =
    task.get_future();
```

Run:

```cpp
task(10);
```

Get result:

```cpp
std::cout << result.get();
```

Output:

```text
100
```

---

# 16. Long Running Function

Suppose:

```cpp
int Compute(std::vector<int> data)
{
    std::this_thread::sleep_for(
        std::chrono::seconds(5)
    );

    return sum;
}
```

This takes time.

---

# 17. Executing Through packaged_task Only

```cpp
taskCompute(data);
```

Execution:

```text
Main Thread
     |
     +--> Compute()
             |
             +--> Wait 5 sec
             |
             +--> Return
```

The main thread remains blocked.

---

# 18. Why This Is Not Enough

Even though we use:

```cpp
packaged_task
```

the work still executes in the current thread.

Therefore:

```text
No concurrency yet.
```

---

# 19. Executing packaged_task in a Thread

Instead of running:

```cpp
taskCompute(data);
```

run:

```cpp
std::thread t(
    std::move(taskCompute),
    data
);
```

Now:

```text
Main Thread
    |
    +--> Creates Child Thread

Child Thread
    |
    +--> taskCompute(data)
            |
            +--> Compute()
```

---

# 20. Why std::move() Is Required

`std::packaged_task` is:

```text
Moveable
```

but:

```text
Not Copyable
```

Copying is forbidden.

Therefore:

```cpp
std::thread t(taskCompute,data);
```

fails.

Correct:

```cpp
std::thread t(
    std::move(taskCompute),
    data
);
```

---

# 21. Move Ownership

```text
Before Move

taskCompute
      |
      +--> Owns Task

After Move

thread
     |
     +--> Owns Task

taskCompute
     |
     +--> Empty
```

---

# 22. Synchronizing with join()

Always wait:

```cpp
t.join();
```

---

# 23. Complete Flow

```cpp
std::packaged_task<int(std::vector<int>)>
    task(Compute);

auto future = task.get_future();

std::thread worker(
    std::move(task),
    data
);

worker.join();

int result = future.get();
```

---

# 24. Execution Timeline

```text
Main Thread
    |
    +--> Create Future
    |
    +--> Start Worker
    |
    +--> Prints:
          "Thread has started computing"

Worker Thread
    |
    +--> Execute Compute()
    |
    +--> Store Result
```

Later:

```text
future.get()
```

retrieves the result.

---

# 25. What Does future.get() Do?

```cpp
future.get();
```

Returns:

```text
Stored Result
```

If result is not ready:

```text
Blocks and waits.
```

If result is ready:

```text
Returns immediately.
```

---

# 26. Important Property

A future ensures:

```text
Consumer waits only when necessary.
```

This is extremely useful for:

- Background computation
- Database queries
- File processing
- Network requests
- Sensor processing

---

# 27. Architecture Diagram

```text
                +----------------+
                |   Main Thread  |
                +----------------+
                         |
                         V
               get_future()
                         |
                         V
                 +--------------+
                 |    Future    |
                 +--------------+
                         ^
                         |
                 stores result
                         |
                         V
             +----------------------+
             |   packaged_task      |
             +----------------------+
                         |
                         V
                  Compute()
                         |
                         V
                 Worker Thread
```

---

# 28. packaged_task vs std::thread

| Feature | std::thread | packaged_task |
|----------|------------|---------------|
| Executes callable | ✅ | ✅ |
| Runs in separate thread | ✅ | Only if placed inside one |
| Captures return value | ❌ | ✅ |
| Creates future | ❌ | ✅ |
| Supports async result retrieval | ❌ | ✅ |

---

# 29. Key Takeaways

### std::thread

```cpp
std::thread
```

- Executes functions
- Ignores return values

---

### std::packaged_task

```cpp
std::packaged_task
```

- Wraps a callable
- Captures return value
- Creates a future

---

### std::future

```cpp
std::future
```

- Holds a result that will be available later
- Retrieves result through `get()`

---

### std::move

Required because:

```cpp
std::packaged_task
```

is move-only.

---

### join

```cpp
thread.join();
```

waits for worker thread completion.

---

# Interview Questions

### Q1: Can std::thread directly return values?

❌ No.

---

### Q2: Which class captures return values from asynchronous execution?

```cpp
std::packaged_task
```

---

### Q3: Which class receives the result?

```cpp
std::future
```

---

### Q4: How do you obtain a future?

```cpp
auto fut = task.get_future();
```

---

### Q5: Why must packaged_task be moved?

Because it is:

```text
Moveable
Not Copyable
```

---

### Q6: Which function retrieves the result?

```cpp
future.get();
```

---

# Memory Aid

```text
Normal Function

Function
   |
   +--> Return Value
```

```text
Thread Function

Function
   |
packaged_task
   |
future
   |
get()
   |
Result
```

Or remember:

```text
std::thread
    = Execute Work

std::packaged_task
    = Execute Work + Capture Result

std::future
    = Read Result Later
```
# Sharing Data Between Threads, Race Conditions, Mutexes, and Deadlocks

> This section explains how threads share data, why race conditions occur, and how `std::mutex` is used to synchronize access to shared resources.

---

# 1. Sharing Data Between Threads

In real-world applications, multiple threads often need access to the same data.

Example:

```text
Thread 1
     |
     +--> Download Part A

Thread 2
     |
     +--> Download Part B
```

Both threads may need to store their results in the same container.

For example:

```cpp
std::list<int> data;
```

where the list represents downloaded file contents.

---

# 2. A Simple Approach: Global Data

One way to share data is to make it global.

```cpp
std::list<int> data;
```

Now every thread can access it.

Example:

```cpp
void Download()
{
    for(int i = 0; i < 10000; i++)
    {
        data.push_back(i);
    }
}
```

```cpp
void Download2()
{
    for(int i = 0; i < 10000; i++)
    {
        data.push_back(i);
    }
}
```

Thread creation:

```cpp
std::thread t1(Download);
std::thread t2(Download2);

t1.join();
t2.join();
```

---

# 3. Expected Result

Each thread inserts:

```text
10,000 elements
```

Therefore:

```text
10,000 + 10,000 = 20,000
```

Expected:

```cpp
data.size() == 20000
```

---

# 4. Actual Result

Sometimes:

```text
19917
19873
19954
19991
```

Every execution may produce a different output.

Why?

---

# 5. The Problem: Simultaneous Access

Two threads execute:

```cpp
data.push_back(...)
```

at the same time.

Timeline:

```text
Thread 1 ----> push_back()
Thread 2 ----> push_back()
```

Both attempt to modify the same object simultaneously.

---

# 6. Race Condition

This situation is called a:

```text
Race Condition
```

Definition:

> A race condition occurs when multiple threads access and modify shared data concurrently, and the final result depends on the unpredictable timing of thread execution.

---

# 7. Why Is It Called a Race?

Imagine:

```text
Thread 1
      \
       >---- Race ----> Shared Data
      /
Thread 2
```

Both threads race to access the same resource first.

The winner changes each run.

---

# 8. Characteristics of Race Conditions

Symptoms:

✅ Random outputs

✅ Intermittent bugs

✅ Difficult debugging

✅ Non-reproducible failures

Example:

```text
Run #1 -> 19917
Run #2 -> 19984
Run #3 -> 19956
Run #4 -> 20000
```

---

# 9. Why Shared Containers Are Not Safe

Operations like:

```cpp
push_back()
erase()
insert()
resize()
```

modify internal container state.

For a list:

```text
Node Links
List Size
Internal Pointers
```

must be updated consistently.

Concurrent modification may corrupt the container.

---

# 10. Solution: Synchronization

We need a mechanism to guarantee:

```text
Only One Thread
Accesses Critical Data
At A Time
```

This process is called:

```text
Synchronization
```

---

# 11. Introducing std::mutex

C++11 provides:

```cpp
std::mutex
```

Header:

```cpp
#include <mutex>
```

Declaration:

```cpp
std::mutex mtx;
```

---

# 12. What Is a Mutex?

Mutex means:

```text
Mutual Exclusion
```

It prevents multiple threads from entering a critical section simultaneously.

Think of it as a key:

```text
Thread needs key
|
+--> enters room
|
+--> leaves room
|
+--> returns key
```

Only one key exists.

---

# 13. Locking a Mutex

Before accessing shared data:

```cpp
mtx.lock();
```

Example:

```cpp
mtx.lock();

data.push_back(i);

mtx.unlock();
```

---

# 14. Critical Section

The protected code is called a:

```text
Critical Section
```

Example:

```cpp
mtx.lock();

data.push_back(i);

mtx.unlock();
```

Everything between:

```cpp
lock()
unlock()
```

is the critical section.

---

# 15. What Happens Internally?

Suppose:

```text
Thread 1
Thread 2
```

both call:

```cpp
mtx.lock();
```

at the same time.

---

### Thread 1

Successfully locks mutex.

```text
Mutex Locked
```

Thread 1 enters critical section.

---

### Thread 2

Attempts:

```cpp
mtx.lock();
```

but:

```text
Mutex Already Locked
```

So:

```text
Thread 2 Waits
```

---

# 16. Wait Queue

Blocked threads are placed into:

```text
Wait Queue
```

Visualization:

```text
Mutex

   [Owner]
      |
      V
   Thread 1

Waiting:
---------
Thread 2
Thread 3
Thread 4
```

---

# 17. Unlocking

When Thread 1 finishes:

```cpp
mtx.unlock();
```

Then:

```text
Mutex Becomes Available
```

Another waiting thread may acquire it.

---

# 18. After Synchronization

```cpp
mtx.lock();

data.push_back(i);

mtx.unlock();
```

Now:

```text
Only One Thread
Can Modify data
At A Time
```

Result:

```cpp
data.size() == 20000
```

every run.

---

# 19. Data Race Eliminated

Without mutex:

```text
Race Condition
```

With mutex:

```text
Synchronized Access
```

Predictable behavior.

---

# 20. Problem with Manual Locking

The following style is dangerous:

```cpp
mtx.lock();

data.push_back(i);

mtx.unlock();
```

Why?

Because anything between those lines may fail.

---

# 21. Example: Early Return

```cpp
mtx.lock();

if(i == 500)
{
    return;
}

data.push_back(i);

mtx.unlock();
```

What happens?

---

# 22. Execution

```text
Thread Locks Mutex
        |
        V
return;
        |
        V
Function Ends
```

The mutex never gets unlocked.

---

# 23. The Consequence

Other thread:

```cpp
mtx.lock();
```

tries to acquire mutex.

But:

```text
Mutex Still Locked
```

So:

```text
Thread Waits Forever
```

---

# 24. Deadlock

This situation is called:

```text
Deadlock
```

Definition:

> A deadlock is a situation where one or more threads wait indefinitely for a resource that can never become available.

---

# 25. Deadlock Timeline

```text
Thread 1
--------
lock()
return()
(no unlock)

Mutex
------
Locked Forever

Thread 2
--------
lock()
wait...
wait...
wait...
forever
```

Program appears frozen.

---

# 26. Symptoms of Deadlock

```text
Application Hangs
CPU Usage Low
No Progress
No Termination
```

Typical debugging symptom:

```text
Program never exits.
```

---

# 27. Root Cause

The mutex owner terminated without releasing ownership.

```text
Acquire Resource
       |
Forget Release
       |
Deadlock
```

---

# 28. Critical Rule

Every:

```cpp
lock()
```

must be matched with:

```cpp
unlock()
```

regardless of:

- Exceptions
- Returns
- Errors
- Abort conditions

---

# 29. The Problem with Manual lock/unlock

Manual management is error-prone because developers may accidentally write:

```cpp
return;
throw;
break;
continue;
```

before:

```cpp
unlock();
```

leading to deadlocks.

---

# 30. Modern C++ Solution (Preview)

Modern C++ normally prefers:

```cpp
std::lock_guard
```

or

```cpp
std::unique_lock
```

instead of:

```cpp
lock();
unlock();
```

because they automatically unlock the mutex when leaving scope.

Example:

```cpp
{
    std::lock_guard<std::mutex> guard(mtx);

    data.push_back(i);
}
```

Automatic unlock:

```text
Enter Scope
      |
Lock Mutex
      |
Leave Scope
      |
Unlock Automatically
```

This topic usually follows immediately after learning basic mutexes.

---

# Race Condition vs Deadlock

| Race Condition | Deadlock |
|---------------|-----------|
| Incorrect result | Program hangs |
| Threads run simultaneously | Threads wait forever |
| Data corruption possible | No progress possible |
| Caused by missing synchronization | Caused by missing unlock or circular waiting |

---

# Key Takeaways

### Shared Data

```cpp
std::list<int> data;
```

can be accessed by multiple threads.

---

### Race Condition

Occurs when:

```text
Multiple Threads
Modify Shared Data
Without Synchronization
```

---

### Mutex

```cpp
std::mutex
```

provides mutual exclusion.

---

### Lock

```cpp
mtx.lock();
```

acquires ownership.

---

### Unlock

```cpp
mtx.unlock();
```

releases ownership.

---

### Deadlock

Occurs when:

```text
Mutex Locked
+
Never Unlocked
```

---

# Interview Questions

### Q1: What is a race condition?

Multiple threads access shared data concurrently and the result depends on execution timing.

---

### Q2: What is a mutex?

A synchronization primitive that allows only one thread at a time to access a critical section.

---

### Q3: What does mutex mean?

```text
Mutual Exclusion
```

---

### Q4: What happens when a locked mutex is requested by another thread?

The thread waits in a queue until the mutex becomes available.

---

### Q5: What is a deadlock?

A situation where threads wait forever and no progress can be made.

---

### Q6: Why is manual lock/unlock dangerous?

Because exceptions or early returns can prevent `unlock()` from executing.

---

# Memory Aid

```text
Race Condition
    =
Too Many Threads
Inside At Once
```

```text
Mutex
    =
One Thread At A Time
```

```text
Deadlock
    =
Locked Forever
```

Simple rule:

```text
Shared Data
      |
No Mutex
      |
Race Condition

Shared Data
      |
Mutex
      |
Safe Access

Mutex
      |
Forgot Unlock
      |
Deadlock
```

# RAII, std::lock_guard, Safe Mutex Handling, and Reducing Lock Contention

> This section extends mutex synchronization by introducing the RAII pattern, `std::lock_guard`, automatic mutex management, and discusses why excessive locking can hurt performance.

---

# 1. The Problem with Manual lock()/unlock()

Previously we protected shared data using:

```cpp
mtx.lock();

data.push_back(i);

mtx.unlock();
```

This works, but it is dangerous.

Why?

Because every path that exits the function must remember to call:

```cpp
mtx.unlock();
```

Examples:

```cpp
return;
throw;
break;
continue;
```

can all bypass the unlock statement.

---

# 2. Example of the Problem

```cpp
mtx.lock();

if(i == 500)
{
    return;
}

data.push_back(i);

mtx.unlock();
```

Execution:

```text
Lock mutex
     |
Return
     |
Function exits
```

The unlock is never reached.

Result:

```text
Mutex stays locked forever.
```

---

# 3. Consequence: Deadlock

Thread 1:

```text
Lock Mutex
     |
Return Early
     |
Never Unlock
```

Thread 2:

```text
Attempts lock()
      |
      V
Wait Forever
```

Result:

```text
Deadlock
```

The application appears frozen.

---

# 4. Better Solution: RAII

Modern C++ solves this problem using:

```text
RAII
```

which stands for:

```text
Resource Acquisition Is Initialization
```

---

# 5. What is RAII?

RAII is one of the most important idioms in Modern C++.

Basic idea:

```text
Acquire Resource
In Constructor

Release Resource
In Destructor
```

Example:

```text
Object Created
      |
Acquire Resource
      |
Use Resource
      |
Object Destroyed
      |
Release Resource
```

---

# 6. Why RAII Works

Local variables automatically execute:

```cpp
Constructor
```

when entering scope.

and

```cpp
Destructor
```

when leaving scope.

Even if the scope exits because of:

```cpp
return;
throw;
exception;
```

the destructor still executes.

This is the key reason RAII is safe.

---

# 7. std::lock_guard

C++11 provides:

```cpp
std::lock_guard
```

Header:

```cpp
#include <mutex>
```

Purpose:

```text
Automatic Mutex Management
```

---

# 8. Using lock_guard

Instead of:

```cpp
mtx.lock();

data.push_back(i);

mtx.unlock();
```

write:

```cpp
std::lock_guard<std::mutex>
    guard(mtx);

data.push_back(i);
```

No manual unlock required.

---

# 9. What Happens Internally?

When lock_guard is created:

```cpp
std::lock_guard<std::mutex>
    guard(mtx);
```

Constructor executes:

```cpp
mtx.lock();
```

automatically.

---

# 10. When Scope Ends

Suppose:

```cpp
{
    std::lock_guard<std::mutex>
        guard(mtx);

    data.push_back(i);

} // scope ends
```

At scope exit:

```cpp
guard.~lock_guard();
```

Destructor executes:

```cpp
mtx.unlock();
```

automatically.

---

# 11. Conceptual View

Manual version:

```text
lock()
   |
work
   |
unlock()
```

RAII version:

```text
Create lock_guard
        |
Auto lock
        |
Work
        |
Destroy lock_guard
        |
Auto unlock
```

---

# 12. Protection Against Early Return

Consider:

```cpp
std::lock_guard<std::mutex>
    guard(mtx);

if(i == 500)
{
    return;
}
```

Execution:

```text
Create Guard
      |
Lock Mutex
      |
Return
      |
Destroy Guard
      |
Unlock Mutex
```

Everything is still safe.

---

# 13. Protection Against Exceptions

```cpp
std::lock_guard<std::mutex>
    guard(mtx);

ThrowException();
```

If exception occurs:

```text
Exception
      |
Stack Unwinding
      |
Guard Destroyed
      |
Mutex Unlocked
```

No deadlock.

---

# 14. Why lock_guard Is Preferred

✅ Simpler

✅ Safer

✅ Exception-safe

✅ Prevents forgotten unlocks

✅ Recommended Modern C++ style

---

# 15. Recommended Rule

Avoid:

```cpp
lock();
unlock();
```

Prefer:

```cpp
std::lock_guard<std::mutex>
```

whenever possible.

---

# 16. Synchronization Still Has a Cost

Although mutexes fix race conditions, they are not free.

Example:

```cpp
for(int i = 0; i < 10000; i++)
{
    std::lock_guard<std::mutex>
        guard(mtx);

    data.push_back(i);
}
```

Every iteration performs:

```text
Lock
Push
Unlock
```

thousands of times.

---

# 17. What Happens During Locking?

Suppose Thread 1 owns the mutex.

```text
Thread 1
     |
     +--> Working
```

Thread 2 attempts:

```cpp
mtx.lock();
```

Result:

```text
Thread 2 Sleeps
```

---

# 18. Waiting Threads Cannot Work

While waiting:

```text
Thread State:
    Blocked
```

The thread does:

```text
No Useful Work
```

until the mutex becomes available.

---

# 19. CPU Utilization Issue

Imagine:

```text
CPU Free
```

but:

```text
Thread Waiting For Mutex
```

Even though CPU resources are available:

```text
Thread Cannot Execute
```

because it is blocked.

---

# 20. Lock Contention

This situation is called:

```text
Lock Contention
```

Many threads compete for the same mutex.

Visualization:

```text
          Mutex
            |
    -----------------
    |       |       |
Thread1 Thread2 Thread3
```

Only one thread can proceed.

---

# 21. Performance Impact

Heavy locking may cause:

- Reduced scalability
- Context-switch overhead
- Increased waiting
- Poor CPU utilization
- Slower execution

---

# 22. Design Principle

Good concurrent systems try to minimize:

```text
Shared State
```

and therefore minimize:

```text
Mutex Usage
```

---

# 23. Alternative Design

Instead of:

```text
All Threads
      |
      V
Shared List
```

each thread can own its own data.

---

# 24. Separate Lists Per Thread

Example:

```cpp
std::list<int> thread1Data;
std::list<int> thread2Data;
```

Thread 1:

```cpp
thread1Data.push_back(...);
```

Thread 2:

```cpp
thread2Data.push_back(...);
```

No shared access.

No mutex needed.

---

# 25. Architecture Comparison

### Shared Data Design

```text
Thread 1 ----\
              \
               > Shared List
              /
Thread 2 ----/
```

Requires:

```text
Mutex
```

---

### Per-Thread Data Design

```text
Thread 1 --> Local List

Thread 2 --> Local List
```

Requires:

```text
No Synchronization
```

during processing.

---

# 26. Final Merge Phase

After:

```cpp
t1.join();
t2.join();
```

main can combine the results.

```cpp
globalList.insert(...);
```

Conceptually:

```text
Thread 1 List ----\
                   \
                    > Final List
                   /
Thread 2 List ----/
```

---

# 27. Why This Is Faster

During downloading:

```text
No Lock
No Wait
No Blocking
```

Each thread operates independently.

Synchronization happens only once during merge.

---

# 28. Lock-Free Thinking

Good concurrent design often follows:

```text
Don't Protect Shared Data

Avoid Shared Data
```

This is usually faster than adding more mutexes.

---

# 29. Design Hierarchy

Preferred order:

```text
1. No Shared State
       ↓
2. Minimal Shared State
       ↓
3. Mutex Protection
       ↓
4. Heavy Locking Everywhere
```

The further down the list:

```text
More Overhead
Less Scalability
```

---

# lock_guard vs Manual Locking

| Feature | lock()/unlock() | lock_guard |
|----------|----------------|------------|
| Automatic unlock | ❌ | ✅ |
| Exception safe | ❌ | ✅ |
| Early-return safe | ❌ | ✅ |
| Easier to use | ❌ | ✅ |
| Recommended | ❌ | ✅ |

---

# Key Takeaways

### RAII

```text
Resource Acquisition
        +
Initialization
```

Acquire resource in constructor.

Release resource in destructor.

---

### lock_guard

```cpp
std::lock_guard<std::mutex>
```

automatically:

```text
Locks Mutex
Unlocks Mutex
```

---

### Safety

Protects against:

```cpp
return;
throw;
exceptions;
```

that could otherwise cause deadlocks.

---

### Performance

Mutexes solve race conditions but introduce:

```text
Blocking
Waiting
Contention
```

---

### Better Design

Often better than:

```text
Shared Resource
+ Mutex
```

is:

```text
Per-Thread Data
+ Final Merge
```

---

# Interview Questions

### Q1: What does RAII stand for?

```text
Resource Acquisition Is Initialization
```

---

### Q2: Why is RAII useful?

It guarantees resources are released automatically through destructors.

---

### Q3: What does lock_guard do?

Automatically locks a mutex in its constructor and unlocks it in its destructor.

---

### Q4: Why is lock_guard safer than lock/unlock?

Because it remains correct even when functions return early or throw exceptions.

---

### Q5: What is lock contention?

Multiple threads competing for the same mutex.

---

### Q6: What is often better than locking?

Reducing or eliminating shared data between threads.

---

# Memory Aid

```text
Manual Locking

lock()
   |
work
   |
unlock()

Easy To Forget
```

```text
lock_guard

Create Object
      |
Auto Lock
      |
Work
      |
Destroy Object
      |
Auto Unlock
```

Golden Rule:

```text
Race Condition?
    |
Use Mutex

Using Mutex?
    |
Use lock_guard

Too Many Mutexes?
    |
Redesign Data Flow
```
# Important std::thread Functions, Thread IDs, Native Handles, Hardware Concurrency, and Thread Delays

> This chapter covers several useful functions of `std::thread`, including thread identification, platform-specific thread handles, CPU core detection, thread naming, and introducing delays using `sleep_for()`.

---

# 1. Useful Functions in std::thread

Besides creating and managing threads, the `std::thread` class provides several utility functions:

```cpp
get_id()
native_handle()
joinable()
hardware_concurrency()
```

In addition, the namespace:

```cpp
std::this_thread
```

provides functionality specific to the currently executing thread.

---

# 2. Getting a Thread ID

Every thread has a unique identifier.

Function:

```cpp
thread.get_id();
```

Example:

```cpp
std::thread t(Process);

auto id = t.get_id();

std::cout << id;
```

Output:

```text
13268
```

(actual value varies each execution)

---

# 3. Return Type of get_id()

The return type is:

```cpp
std::thread::id
```

which is a nested type inside `std::thread`.

Conceptually:

```cpp
std::thread
    |
    +-- id
```

---

# 4. Why Thread IDs Are Useful

Thread IDs help:

- Identify threads
- Debug concurrent applications
- Log thread activity
- Track ownership of resources

Example:

```cpp
std::cout
    << "Running in thread "
    << std::this_thread::get_id();
```

---

# 5. Printing Thread IDs

Although:

```cpp
std::thread::id
```

is a class type,

the insertion operator is overloaded.

Therefore:

```cpp
std::cout << id;
```

works directly.

---

# 6. Thread Identification Example

```cpp
void Process()
{
    std::cout
        << std::this_thread::get_id();
}

int main()
{
    std::thread t(Process);

    std::cout
        << t.get_id();

    t.join();
}
```

Both values will be identical.

---

# 7. native_handle()

Another useful function:

```cpp
thread.native_handle()
```

Purpose:

```text
Obtain
Platform-Specific
Thread Handle
```

---

# 8. Why native_handle Exists

The C++ thread library is:

```text
Cross Platform
```

but operating systems expose additional thread functionality.

Examples:

```text
Windows API
Linux pthread API
```

To use those APIs, we need the operating-system thread handle.

---

# 9. Platform-Specific Types

### Windows

```cpp
HANDLE
```

---

### Linux

```cpp
pthread_t
```

---

### C++ Interface

```cpp
thread.native_handle()
```

returns the underlying native representation.

---

# 10. Typical Use Cases

Native handles may be needed for:

- Setting thread names
- Changing priorities
- Processor affinity
- Scheduling policies
- Debugging tools

---

# 11. Viewing Threads During Debugging

Modern IDEs can display all running threads.

Example:

```text
Debug
   |
Windows
   |
Threads
```

You may see:

```text
Main Thread
Worker Thread #1
Worker Thread #2
```

and additional operating-system-created threads.

---

# 12. Why More Threads Appear Than Expected

Even simple applications often contain:

```text
Main Thread
```

plus several operating system worker threads.

Example:

```text
DLL Loading
Background Services
Runtime Support
```

These are not necessarily created by your code.

---

# 13. Naming Threads

A common debugging problem:

```text
Thread #1234
Thread #8472
Thread #2500
```

is difficult to understand.

Instead we would like:

```text
NetworkThread
RendererThread
DownloadThread
```

---

# 14. Standard C++ Limitation

Current C++ thread library provides:

```text
No Portable Thread Naming API
```

Therefore we often use platform-specific APIs.

---

# 15. Naming Threads on Windows

Windows provides:

```cpp
SetThreadDescription()
```

Header:

```cpp
#include <Windows.h>
```

---

# 16. Example: SetThreadDescription

```cpp
SetThreadDescription(
    t.native_handle(),
    L"MyThread"
);
```

---

# 17. Parameters

First parameter:

```cpp
t.native_handle()
```

Windows thread handle.

---

Second parameter:

```cpp
L"MyThread"
```

Wide-character string.

---

# 18. Why Prefix L?

```cpp
L"MyThread"
```

means:

```cpp
const wchar_t*
```

which is what the Windows API expects.

---

# 19. Result

Before:

```text
Thread #19384
```

After:

```text
MyThread
```

Debugging becomes much easier.

---

# 20. Linux Equivalent

Linux uses:

```cpp
pthread_setname_np()
```

instead of:

```cpp
SetThreadDescription()
```

Example:

```cpp
pthread_setname_np(
    pthread_self(),
    "Worker"
);
```

---

# 21. hardware_concurrency()

Static function:

```cpp
std::thread::hardware_concurrency()
```

Purpose:

```text
Query Available Hardware Threads
```

---

# 22. Example

```cpp
std::cout
    << std::thread::hardware_concurrency();
```

Possible output:

```text
8
```

---

# 23. What Does It Represent?

Typically:

```text
Logical CPU Cores
```

available to the process.

Examples:

```text
4
8
16
32
```

depending on the processor.

---

# 24. Why Is It Useful?

Suppose:

```cpp
Image Processing
Simulation
Data Analysis
```

requires worker threads.

You can determine a reasonable thread count:

```cpp
unsigned n =
    std::thread::hardware_concurrency();
```

---

# 25. General Guideline

Very often:

```text
Optimal Thread Count
≈
Available CPU Cores
```

Example:

```text
8 Cores
→
8 Worker Threads
```

This is a practical guideline, not a strict rule.

---

# 26. Namespace std::this_thread

Another useful namespace:

```cpp
std::this_thread
```

It contains functions that affect the currently running thread.

Think:

```text
this thread
=
the thread executing this code
```

---

# 27. Getting Current Thread ID

Inside a thread:

```cpp
std::this_thread::get_id();
```

Example:

```cpp
void Process()
{
    std::cout
        << std::this_thread::get_id();
}
```

Returns:

```text
Current Thread ID
```

---

# 28. Difference Between the Two get_id() Versions

### From Thread Object

```cpp
t.get_id();
```

Returns:

```text
ID of t
```

---

### From Current Thread

```cpp
std::this_thread::get_id();
```

Returns:

```text
ID of currently running thread
```

---

# 29. Delaying a Thread

Sometimes we want to pause execution.

For example:

- Animation
- Polling
- Simulations
- Delayed retry logic

Use:

```cpp
std::this_thread::sleep_for()
```

---

# 30. sleep_for()

Example:

```cpp
std::this_thread::sleep_for(
    std::chrono::seconds(1)
);
```

Effect:

```text
Thread Sleeps
For One Second
```

---

# 31. Required Headers

```cpp
#include <thread>
#include <chrono>
```

---

# 32. Example

```cpp
for(int i = 0; i < 5; i++)
{
    std::cout << i;

    std::this_thread::sleep_for(
        std::chrono::seconds(1)
    );
}
```

Output:

```text
0
(wait)

1
(wait)

2
(wait)

3
(wait)

4
```

---

# 33. Available Duration Types

The `chrono` library supports many units.

### Seconds

```cpp
std::chrono::seconds(1)
```

---

### Milliseconds

```cpp
std::chrono::milliseconds(500)
```

---

### Microseconds

```cpp
std::chrono::microseconds(200)
```

---

### Nanoseconds

```cpp
std::chrono::nanoseconds(100)
```

---

### Minutes

```cpp
std::chrono::minutes(2)
```

---

### Hours

```cpp
std::chrono::hours(1)
```

---

# 34. Execution Flow

Without sleep:

```text
Print A
Print B
Print C
```

almost instantly.

---

With sleep:

```text
Print A
(wait)
Print B
(wait)
Print C
```

Controlled timing.

---

# 35. Common Use Cases of sleep_for()

### Animation

```cpp
Move Object
sleep_for(16 ms)
Render Again
```

---

### Retry Logic

```cpp
Connection Failed
sleep_for(5 sec)
Retry
```

---

### Polling

```cpp
Check Sensor
sleep_for(100 ms)
Check Again
```

---

# Important Thread Utilities Summary

| Function | Purpose |
|-----------|----------|
| `get_id()` | Get thread ID |
| `native_handle()` | Access OS thread handle |
| `joinable()` | Check joinability |
| `hardware_concurrency()` | Query CPU concurrency level |
| `this_thread::get_id()` | Get current thread ID |
| `this_thread::sleep_for()` | Pause current thread |

---

# Key Takeaways

### Thread ID

```cpp
t.get_id()
```

returns:

```cpp
std::thread::id
```

---

### Native Handle

```cpp
t.native_handle()
```

gives access to platform-specific APIs.

---

### Thread Naming

Windows:

```cpp
SetThreadDescription()
```

Linux:

```cpp
pthread_setname_np()
```

---

### CPU Query

```cpp
std::thread::hardware_concurrency()
```

returns the available hardware concurrency level.

---

### Current Thread

```cpp
std::this_thread::get_id()
```

returns the ID of the thread currently executing.

---

### Sleep

```cpp
std::this_thread::sleep_for(...)
```

pauses the current thread for a specified duration.

---

# Interview Questions

### Q1: How do you get the ID of a thread?

```cpp
t.get_id();
```

---

### Q2: What is the return type?

```cpp
std::thread::id
```

---

### Q3: Why use native_handle()?

To access operating-system-specific thread APIs.

---

### Q4: What does hardware_concurrency() return?

The number of hardware-supported concurrent execution units (typically logical CPU cores).

---

### Q5: How do you get the ID of the currently executing thread?

```cpp
std::this_thread::get_id();
```

---

### Q6: How do you sleep for one second?

```cpp
std::this_thread::sleep_for(
    std::chrono::seconds(1)
);
```

---

# Memory Aid

```text
Thread Object
    |
    +--> get_id()
    |
    +--> native_handle()
    |
    +--> join()
```

```text
this_thread
    |
    +--> get_id()
    |
    +--> sleep_for()
```

```text
hardware_concurrency()
    |
    +--> How many CPU cores can help me?
```

Rule of thumb:

```text
Need Thread Identity?
    -> get_id()

Need Platform API?
    -> native_handle()

Need Delay?
    -> sleep_for()

Need CPU Count?
    -> hardware_concurrency()
```
