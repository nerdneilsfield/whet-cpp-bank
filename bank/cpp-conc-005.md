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

## 解析

正确答案是 B。互斥量通过临界区保护共享状态，适合多步复合操作而不只是单个原子读写。选项 B 的表述“｀lg｀ 对象离开其作用域（析构）时”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
