---
qid: cpp-conc-adv-007
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

以下代码中，3 个线程同时调用 `init()`，"initialized" 会被打印几次？

```cpp
std::once_flag flag;

void init() {
    std::call_once(flag, []() {
        std::cout << "initialized" << std::endl;
    });
}

int main() {
    std::thread t1(init), t2(init), t3(init);
    t1.join(); t2.join(); t3.join();
}
```

A. 3
B. 1
C. 0
D. 不确定，取决于线程调度

## 解析

正确答案是 B。`std::call_once` 配合 `std::once_flag` 保证指定初始化动作只成功执行一次。选项 B 的表述“1”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
