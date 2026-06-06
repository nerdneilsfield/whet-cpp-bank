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
