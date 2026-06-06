---
qid: cpp-real-nk-018
type: single
kp: [cpp-polymorphism, cpp-classes]
primary_kp: cpp-polymorphism
difficulty: easy
answer_key: A
tags: [interview-real, nowcoder]
---

C++ 中虚函数（virtual）表的建立时间是：

A. **编译期**（vtable 布局在编译时确定）
B. 运行期（程序启动时构造 vtable）
C. 链接期（链接器生成 vtable）
D. 运行期（创建第一个对象时生成 vtable）

---

**解析：**

vtable（虚函数表）在**编译期**就确定了布局：

- 编译器在编译过程中，遍历每个多态类及其虚函数声明，生成 vtable 的结构
- vtable 是一个**静态只读数组**，包含函数指针条目
- vtable 的数据存放在程序只读数据段（`.rodata`）
- 所有对象共享同一个 vtable（相同类）

**vptr（虚函数表指针）**的赋值发生在运行期（构造函数调用时），但 vtable 本身编译期已完全确定。

常见的"vtable 是运行期动态创建"的说法是错误的。vtable 不是像 Java 的类元数据那样在运行时构建。

**来源：** CSDN C++ 虚函数原理专题 / Itanium C++ ABI

## Explanation

正确答案是 A。
vtable（虚函数表）在编译期就确定了布局： 编译器在编译过程中，遍历每个多态类及其虚函数声明，生成 vtable 的结构 vtable 是一个静态只读数组，包含函数指针条目 vtable 的数据存放在程序只读数据段（.rodata） 所有对象共享同一个 vtable（相同类） *vptr（虚函数表指针）的赋值发生在运行期（构造函数调用时），但 vtable 本身编译期已完全确定。
常见的"vtable 是运行期动态创建"的说法是错误的。vtable 不是像 Java 的类元数据那样在运行时构建。
