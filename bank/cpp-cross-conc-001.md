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

## Explanation

B 正确：子线程按引用修改同一个 `x`，并先打印 `thread: x=42`。`join()` 会阻塞主线程直到子线程结束，因此主线程之后看到的也是 42。关键误区是把线程启动误认为主线程继续竞争打印；本题中 `join()` 建立了等待关系。
