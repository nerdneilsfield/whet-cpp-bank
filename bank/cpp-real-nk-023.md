---
qid: cpp-real-nk-023
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: D
tags: [interview-real, alibaba]
---

C++ 的五大内存分区不包括：

A. 栈区（Stack）
B. 堆区（Heap）
C. 全局/静态存储区（Global/Static）
D. 寄存器区（Register）

---

**解析：**

C++ 标准内存五大分区（Linux 常见划分）：

1. **栈区**：局部变量、函数参数、返回地址。自动分配释放，LIFO，大小约 8MB（可调 ulimit）
2. **堆区**：`malloc`/`new` 动态分配，需手动释放。碎片化，分配慢
3. **全局/静态存储区**：全局变量、`static` 变量。程序启动分配，结束释放
4. **常量存储区（.rodata）**：字符串字面量、`const` 全局变量。只读，程序生命周期内存在
5. **代码区（.text）**：程序代码（机器指令）。只读，可共享

Linux /proc/PID/maps 中可见分段：
```
.text    → 代码段
.rodata  → 只读数据
.data    → 已初始化全局/静态变量
.bss     → 未初始化全局/静态变量（BSS 实际不占文件，只是一个占位）
heap     → 堆（brk/mmap）
stack    → 栈（高地址向低增长）
```

**寄存器区**属于 CPU 硬件范畴，不归 C++ 的分区——虽然 register 关键字存 在（已废弃 C++17），但变量在寄存器中不构成一个"内存区域"。

**来源：** 网易 C++ 内存分区面试题 / APUE