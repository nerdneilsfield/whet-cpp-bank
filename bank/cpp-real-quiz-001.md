---
qid: cpp-real-quiz-001
type: single
kp: [cpp-types]
primary_kp: cpp-types
difficulty: hard
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17/20 标准，以下程序的行为是？

```cpp
#include <iostream>
int main() {
    unsigned short zero = 0, one = 1;
    if (zero - one < zero)
        std::cout << "less";
    else
        std::cout << "more";
}
```

A. 程序保证输出 `less`
B. 程序保证输出 `more`
C. 编译错误
D. 行为未定义

---

**解析：**

C++ 算术运算符 `-` 要求两个操作数先经过**整型提升（integer promotion，[conv.prom]）**。在常见平台上 `sizeof(unsigned short) < sizeof(int)`，`unsigned short` 的所有值都能被 `int` 完整表示，所以两个操作数都被**提升为 `int`**（而不是 `unsigned int`）。

于是 `zero - one` 在带符号 int 域内算 `0 - 1 = -1`（没有溢出，没有回卷），随后 `-1 < 0` 为 true，输出 `less`。

新人最容易选 B：直觉上 unsigned 之间相减应该回卷到 `65535`，但那只发生在两边已经是 `unsigned int`/`unsigned long` 时；`unsigned short` 还没那么大，先被升成 int 了。

**来源：** cppquiz.org Question #365（C++17 [conv.prom]）

## Explanation

正确答案是 A。
C++ 算术运算符 - 要求两个操作数先经过整型提升（integer promotion，[conv.prom]）。在常见平台上 sizeof(unsigned short) < sizeof(int)，unsigned short 的所有值都能被 int 完整表示，所以两个操作数都被提升为 int（而不是 unsigned int）。
于是 zero - one 在带符号 int 域内算 0 - 1 = -1（没有溢出，没有回卷），随后 -1 < 0 为 true，输出 less。
新人最容易选 B：直觉上 unsigned 之间相减应该回卷到 65535，但那只发生在两边已经是 unsigned int/unsigned long 时；unsigned short 还没那么大，先被升成 int 了。
