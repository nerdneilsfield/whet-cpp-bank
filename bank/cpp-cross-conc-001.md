---
qid: cpp-cross-conc-001
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <iostream>
#include <thread>

int main() {
    int x = 0;
    std::thread t([&x]() {
        x = 42;
        std::cout << "thread: x=" << x << "\n";
    });
    t.join();
    std::cout << "main: x=" << x << "\n";
    return 0;
}
```

A. `main: x=0` 然后 `thread: x=42`
B. `thread: x=42` 然后 `main: x=42`
C. `thread: x=42` 然后 `main: x=0`
D. 未定义行为，输出不确定

> **提示：** `join()` 阻塞主线程，直到子线程执行完毕。lambda 按引用捕获 `x`。
