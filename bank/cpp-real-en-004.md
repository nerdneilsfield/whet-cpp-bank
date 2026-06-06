---
qid: cpp-real-en-004
type: single
kp: [cpp-memory-mgmt, cpp-concurrency]
primary_kp: cpp-memory-mgmt
difficulty: easy
answer_key: C
tags: [interview-real, interviewbit]
---
`volatile` 关键字在嵌入式 C++ 中为什么至关重要？

A. 它让变量的访问变成原子操作
B. 它使得变量可以被多个线程安全访问
C. 它阻止编译器对变量的读写进行优化，确保每次访问都从实际地址读取
D. 它自动将变量声明为 `static`

---

**解析：**

`volatile` 告诉编译器：该变量的值可能在任何时刻被编译器不可预知的方式改变（如硬件寄存器、ISR 中修改）。因此编译器必须：
1. 每次读取都从实际内存地址读取，不能使用寄存器中的缓存值。
2. 每次写入都立即写入内存，不能优化掉"冗余"写。

注意：`volatile` **不**提供原子性，也不保证线程安全（线程安全需要 `std::atomic`）。它只解决编译器优化问题。

**来源：** InterviewBit "C++ Interview Questions" — volatile