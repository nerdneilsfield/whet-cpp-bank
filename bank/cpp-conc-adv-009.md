---
qid: cpp-conc-adv-009
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: A
---

以下代码的输出是什么？

```cpp
#include <iostream>
#include <future>
#include <thread>

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t([&p]() {
        p.set_value(42);
    });

    std::cout << f.get() << std::endl;
    t.join();
}
```

A. 42
B. 0
C. 编译错误
D. 运行时死锁
