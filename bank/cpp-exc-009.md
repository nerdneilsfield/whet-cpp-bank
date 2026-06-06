---
qid: cpp-exc-009
type: single
kp: [cpp-exceptions]
difficulty: easy
answer_key: B
---

# C++ 异常处理：栈展开（stack unwinding）

异常抛出后，在异常传播过程中，已构造的局部对象会发生什么？

A. 局部对象的析构函数不会被调用，内存直接回收
B. 局部对象的析构函数会被自动调用（栈展开）
C. 局部对象的析构函数只在 `catch` 块结束后调用
D. 由编译器决定，行为未定义
