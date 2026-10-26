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
