---
qid: cpp-real-multi-007
type: multi
kp: [cpp-undefined-behavior]
primary_kp: cpp-undefined-behavior
difficulty: hard
answer_key: [A, C, D]
tags: [interview-real, multi-vendor]
---
C++ 标准定义了几种"未定行为"等级。以下哪些是 **Undefined Behavior（UB）** 而非 implementation-defined 或 unspecified（多选）？

A. 解引用空指针（`int* p = nullptr; *p;`）
B. `int x = 1; std::cout << sizeof(int);` 在不同平台输出不同（4/8）
C. 有符号整型溢出（`INT_MAX + 1`）
D. 对未初始化的局部变量进行读取（`int x; std::cout << x;`）
E. 函数实参的求值顺序（`f(g(), h())` 中 g 和 h 谁先执行）

---

**解析：**

正确答案：**A、C、D**。

**三种"非确定"行为的层次：**

| 等级 | 定义 | 标准要求 |
|------|------|----------|
| **Undefined Behavior (UB)** | 程序在所有平台上都没有任何保证；编译器可任意优化 | 没有定义 |
| **Implementation-defined** | 每个实现必须做出选择并**文档化** | 必须文档化 |
| **Unspecified** | 多种合法行为之一，实现无需文档化 | 任选一种 |

**A 正确（UB）：** 解引用空指针是经典 UB。编译器在优化时**可以假设这不会发生**——这就是为什么 `if (p == nullptr) { /*...*/ } *p;` 中条件分支可能被优化掉。

**B 错误（implementation-defined）：** `sizeof(int)` 由实现定义，必须文档化为某个固定值。

**C 正确（UB）：** **有符号整型溢出是 UB**！（无符号溢出是 well-defined 的 wraparound）。这意味着 `for (int i = 0; i < INT_MAX; ++i)` 中 ++i 不能假设有限循环——编译器可能优化为无限循环或省略。

**D 正确（UB）：** 读取未初始化的非 static 局部变量是 UB（自 C++14 起更严格）。

**E 错误（unspecified）：** 函数参数求值顺序是 **unspecified**（C++11/14），不是 UB——只是顺序不定，但每个参数仍会被求值且无副作用冲突。**C++17 引入了部分排序：函数调用中 `f(a, b, c)` 仍是 unspecified，但 `a->b()` 中 `a` 先于 `b()` 被求值。**

**UB 的危险性：**
```cpp
int *p = nullptr;
if (cond) p = &x;
*p = 1;             // 若 cond=false → UB → 编译器可假设 cond 永远为 true!
```
这种"time travel"优化让 UB 成为难以追查的 bug 源。

**来源：** 跨厂 C++ UB 高频陷阱（参考：cppreference、John Regehr《A Guide to Undefined Behavior in C and C++》）