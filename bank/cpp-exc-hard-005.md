---
qid: cpp-exc-hard-005
type: single
kp: [cpp-exceptions]
difficulty: hard
answer_key: B
---

跨线程传递异常的标准方式是？

```cpp
#include <exception>
#include <future>

void worker(std::promise<int>& p) {
    try {
        // ...
        throw std::runtime_error("err");
    } catch (...) {
        p.set_exception(std::current_exception());  // ①
    }
}
```

关于 ① 处机制的描述，下列正确的是？

A. `std::current_exception` 返回 `std::exception*`，可直接通过指针在线程间传递
B. `std::current_exception()` 返回 `std::exception_ptr`——一个共享所有权的"异常容器"，可跨线程拷贝/传递。接收方调用 `std::rethrow_exception(eptr)` 即可在自己的栈上重新抛出该异常，保留动态类型。这是 `promise/future`、`std::async` 等异步设施跨线程传递异常的标准机制
C. 异常对象本身可以直接复制到另一线程的栈上，无需特殊设施
D. 跨线程异常传递在 C++ 中是 UB

## Explanation

`std::exception_ptr`（C++11）是"异常的句柄"，类似引用计数共享指针，内部持有对底层异常对象（实际由实现自管理的存储）的引用。`std::current_exception()` 在 catch 内捕获当前异常并返回 `exception_ptr`；该对象可被拷贝、移动、跨线程传递。接收方通过 `std::rethrow_exception(eptr)` 在自己的栈上以正确的动态类型重新抛出。`std::promise::set_exception` 和 `std::async` 的 future 异常传递均基于此机制。重要保证：动态类型保留——可在另一线程用 `catch (std::runtime_error&)` 等捕获派生类型。
