---
qid: cpp-ub-short-003
type: short
kp: [cpp-undefined-behavior]
difficulty: medium
rubric:
  - 指出读取未初始化的对象（除 unsigned char/byte 外）是 UB
  - 解释为什么不是简单地读到"随机值"（编译器可能假定不会发生）
  - 给出常见出错场景（栈上的 int 未初始化、new 出的非类对象）
  - 提到避免方法（默认初始化为零、使用 {} 值初始化、开启编译器/静态分析警告）
---
请解释为什么读取未初始化变量在 C++ 中是未定义行为，并说明如何避免。

---

**参考答案：**

C++ 规定读取一个尚未初始化（不可确定值，indeterminate value）的对象通常是 UB（仅 `unsigned char`/`std::byte` 这类用于检查字节的类型例外）。这并非简单地读到"随机值"——编译器可以基于"UB 不会发生"的前提删除分支或改变代码顺序，导致程序行为极不可预测。常见场景如栈上声明的 `int i;` 未赋值就使用、`new int` 出来的内存未初始化就读取等。避免方法包括：声明时直接 `int i = 0;` 或 `int i{};`、用构造函数初始化成员、使用 `std::optional`，并开启 `-Wuninitialized` 等编译警告或借助 sanitizer 检测。