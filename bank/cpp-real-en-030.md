---
qid: cpp-real-en-030
type: single
kp: [cpp-types, cpp-type-sizes]
primary_kp: cpp-types
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz]
---
以下代码：

```cpp
unsigned short a = 1;
unsigned short b = 2;
auto c = a - b;
```

这段代码中 `c` 的类型和值是什么？

A. `unsigned short`，值为 65535（假设 `unsigned short` 16 位）
B. `int`，值为 -1（整型提升导致结果为有符号 int）
C. `unsigned short`，值为 -1（负数赋给无符号类型）
D. 编译错误：不能对 `unsigned short` 做减法

---

**解析：**

这是 C++ 中**整型提升（integral promotion）**导致的常见陷阱。

在 C++ 中，所有比 `int` 小的整数类型（`bool`、`char`、`short`、`unsigned short` 等）在参与算数运算前都会被提升为 `int`（如果 `int` 能表示所有源类型值）。因此：

1. `a` 和 `b` 从 `unsigned short` 提升为 `int`
2. `1 - 2` 在 `int` 类型下计算，结果为 `-1`
3. `auto c = -1`，`c` 的类型是 `int`，值为 `-1`

如果希望结果为 `unsigned short` 回绕值（65535），需要显式转换：`auto c = static_cast<unsigned short>(a - b);`

**来源：** cppquiz #3 "Integral Promotion"
