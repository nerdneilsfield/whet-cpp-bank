---
qid: cpp-conc-016
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

# 代码阅读：死锁识别

```cpp
std::mutex m1, m2;

void thread_A() {
    std::lock_guard<std::mutex> lg1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::lock_guard<std::mutex> lg2(m2);
}

void thread_B() {
    std::lock_guard<std::mutex> lg1(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::lock_guard<std::mutex> lg2(m1);
}

int main() {
    std::thread ta(thread_A), tb(thread_B);
    ta.join(); tb.join();
}
```

该程序最可能出现什么问题？

A. 编译错误  
B. 数据竞争  
C. 死锁：两线程互相等待对方持有的锁  
D. `std::terminate()`，因为漏掉了 `detach()`

## 解析

正确答案是 C。互斥量通过临界区保护共享状态，适合多步复合操作而不只是单个原子读写。选项 C 的表述“死锁：两线程互相等待对方持有的锁”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
