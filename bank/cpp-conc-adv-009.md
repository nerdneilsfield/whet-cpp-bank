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

## Explanation

正确答案是 A。`std::promise` 负责设置结果，关联的 `std::future` 负责等待并取得结果。选项 A 的表述“42”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
