---
qid: cpp-real-en-003
type: multi
kp: [cpp-concurrency, cpp-functions]
primary_kp: cpp-concurrency
difficulty: medium
answer_key: ["A", "B", "D"]
tags: [interview-real, interviewbit]
---
关于 ISR（Interrupt Service Routine，中断服务例程）及 C++ 代码在 ISR 中的限制，以下哪些说法是正确的？（多选）

A. ISR 中变量声明应使用 `volatile` 关键字，防止编译器优化掉看似冗余但对中断至关重要的读写
B. ISR 中不能使用 `new` / `delete`（堆分配），因为堆操作不是线程安全的且可能触发锁
C. ISR 中可以直接调用 `printf` 进行调试输出
D. ISR 应尽量短小快速，避免长时间占用 CPU
E. ISR 中可以使用 `std::mutex` 进行同步

---

**解析：**

ISR 的限制包括：
- **`volatile`**：告知编译器该变量可能被中断等外部因素修改，防止优化掉重复读/写。
- **不能 `new` / `delete`**：堆分配内部可能加锁，ISR 中加锁可能导致死锁（ISR 和主程序互相等待）。
- **不能 `printf`**：格式化输出通常是非重入的（non-reentrant），且涉及 I/O 等待，违背 ISR 短小快速原则。
- **不能 `std::mutex`**：互斥锁操作可能阻塞，ISR 中不允许阻塞；某些 RTOS 提供了 ISR-safe 的同步原语（如信号量 fromISR 版本）。

**来源：** InterviewBit "C++ Interview Questions" — ISR

## Explanation

正确答案是 ["A", "B", "D"]。
ISR 的限制包括： volatile：告知编译器该变量可能被中断等外部因素修改，防止优化掉重复读/写。
不能 new / delete：堆分配内部可能加锁，ISR 中加锁可能导致死锁（ISR 和主程序互相等待）。
不能 printf：格式化输出通常是非重入的（non-reentrant），且涉及 I/O 等待，违背 ISR 短小快速原则。
