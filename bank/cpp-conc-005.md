---
qid: cpp-conc-005
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: B
---

# 认知：`std::lock_guard` 的解锁时机

`std::lock_guard<std::mutex> lg(mtx);` 会在何时自动解锁互斥量？

A. 调用 `lg.unlock()` 时  
B. `lg` 对象离开其作用域（析构）时  
C. 当前函数返回时，无论 `lg` 在哪个作用域  
D. 程序退出时  
