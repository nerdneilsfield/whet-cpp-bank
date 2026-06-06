---
qid: cpp-real-ali-005
type: single
kp: [cpp-memory-mgmt, cpp-type-sizes]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: C
tags: [interview-real, alibaba]
---
关于 C++ 程序的内存分区，以下哪个说法是正确的？

A. 全局变量存储在栈区，函数执行结束后自动释放
B. 使用 malloc 分配的内存位于栈区，free 后归还操作系统
C. 字符串常量 "hello" 存储在常量区（只读），修改它是 UB
D. static 局部变量存储在栈区，只在第一次调用时初始化

---

**解析：**

选 C。C++ 程序五大内存分区：

| 分区 | 内容 | 特点 |
|------|------|------|
| 栈 | 局部变量、函数参数、返回地址 | 自动分配释放，大小有限（通常 1-8MB） |
| 堆 | malloc/new 分配的对象 | 手动管理，大容量，碎片化 |
| 全局/静态区 | 全局变量、static 变量 | 程序启动分配，结束释放 |
| 常量区 | 字符串常量、const 全局 | 只读，修改是 UB |
| 代码区 | 程序指令 | 只读，可共享 |

A 错，全局变量在全局/静态区，不在栈。B 错，malloc 在堆，free 通常不归还 OS 而归还给进程堆管理。D 错，static 局部变量在全局/静态区（数据段），不是栈。它第一次调用时初始化，但存储位置是静态区。

注意区别：`static int a = 0;` 存储在 .bss（未初始化数据段），`static int a = 1;` 存储在 .data（已初始化数据段）。

**来源：** 阿里 C++ 后端面试

## Explanation

正确答案是 C。
B 错，malloc 在堆，free 通常不归还 OS 而归还给进程堆管理；D 错，static 局部变量在全局/静态区（数据段），不是栈。
注意区别：static int a = 0; 存储在 .bss（未初始化数据段），static int a = 1; 存储在 .data（已初始化数据段）。
