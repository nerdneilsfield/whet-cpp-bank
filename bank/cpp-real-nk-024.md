---
qid: cpp-real-nk-024
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: A
tags: [interview-real, nowcoder]
---

关于堆（heap）和栈（stack）的区别，**错误**的是：

A. **栈向高地址增长，堆向低地址增长**
B. 栈分配速度快（仅修改 sp 寄存器），堆分配慢（涉及空闲链表查找/系统调用）
C. 栈大小受限（默认约 8MB），堆大小受限于物理内存和虚拟地址空间
D. 栈由编译器自动管理，堆需要手动分配释放（或用 RAII）

---

**解析：**

**栈向低地址增长，堆向高地址增长**（典型 Linux/Windows x86 实现），A 描述反了。

```
高地址  ┌──────────┐
        │   Stack  │ ← 向低增长 (push 时 sp 减小)
        │    ↓    │
        │          │
        │    ↑    │
        │   Heap  │ ← 向高增长 (brk/sbrk 增大)
        ├──────────┤
        │   .bss   │
        │  .data   │
        │  .rodata │
        │  .text   │
低地址  └──────────┘
```

其他对比：
- **生长方向**：栈向下，堆向上
- **分配速度**：栈快（O(1) sp 修改），堆慢（freelist 查找、可能 mmap/brk）
- **碎片**：栈无碎片（LIFO），堆有内外部碎片
- **生命周期**：栈随函数返回自动释放，堆需要手动管理
- **大小**：栈默认 8MB（Linux），堆可达数 GB

**来源：** 牛客网 C++ 高频面试题 / CSDN 八股