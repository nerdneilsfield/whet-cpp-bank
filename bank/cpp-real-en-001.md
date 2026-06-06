---
qid: cpp-real-en-001
type: single
kp: [cpp-memory-mgmt, cpp-io]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: B
tags: [interview-real, interviewbit]
---
嵌入式系统中如何实现 memory-mapped I/O（内存映射 I/O）？以下关于访问硬件寄存器的说法正确的是？

A. 使用 `new` 运算符动态分配寄存器地址
B. 将外设寄存器地址 `reinterpret_cast` 为指针后直接读写
C. 通过文件 I/O 函数 `fread` / `fwrite` 访问寄存器
D. 使用 `malloc` 分配 I/O 空间

---

**解析：**

Memory-mapped I/O 是将外设寄存器映射到 CPU 的地址空间中，使 CPU 可以像访问普通内存一样读写寄存器。C++ 中通常通过 `reinterpret_cast` 将物理地址转为指针，然后用 `volatile` 防止编译器优化掉看似"无用"的读写（因为寄存器读写可能有副作用）。例如：

```cpp
auto reg = reinterpret_cast<volatile uint32_t*>(0x40021000);
*reg = 0x01;  // 写入寄存器
```

`new` 和 `malloc` 用于堆分配，不适用于固定硬件地址；文件 I/O 则完全不是硬件寄存器访问的方式。

**来源：** InterviewBit "C++ Interview Questions" — Memory-Mapped I/O

## Explanation

正确答案是 B。
Memory-mapped I/O 是将外设寄存器映射到 CPU 的地址空间中，使 CPU 可以像访问普通内存一样读写寄存器。C++ 中通常通过 reinterpret_cast 将物理地址转为指针，然后用 volatile 防止编译器优化掉看似"无用"的读写（因为寄存器读写可能有副作用）。例如： new 和 malloc 用于堆分配，不适用于固定硬件地址；文件 I/O 则完全不是硬件寄存器访问的方式。
