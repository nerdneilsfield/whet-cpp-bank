---
qid: cpp-cross-conc-004
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <iostream>
#include <future>

int compute(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> f = std::async(std::launch::async, compute, 3, 7);
    std::cout << "waiting...\n";
    int result = f.get();
    std::cout << "result=" << result << "\n";
    return 0;
}
```

A. `result=10` 然后 `waiting...`
B. `waiting...` 然后 `result=0`
C. `waiting...` 然后 `result=10`
D. 编译错误

> **提示：** `std::async(launch::async, ...)` 立即在新线程异步执行任务；`future.get()` 阻塞直到结果就绪并返回该值。主线程先打印 `waiting...`，再调用 `get()` 获取计算结果。
