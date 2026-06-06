---
qid: cpp-real-quiz-018
type: single
kp: [cpp-operators]
primary_kp: cpp-operators
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
int main() {
    int a = 6, b = 5, c = 5;
    std::cout << (a & b == c);
}
```

A. `4`（认为先算 `a & b = 4`，再 `4 == 5` 为 `0`，再输出 `4`？）
B. `0`
C. `1`
D. 编译错误

---

**解析：**

[expr]：C++ 中运算符优先级 `==` **高于** 按位与 `&`。所以 `a & b == c` 等价于 `a & (b == c)`，**不是** `(a & b) == c`。

`b == c` → `5 == 5` 为 `true`，提升为 `int(1)`。
`a & 1` → `6 & 1 = 0`。
输出 `0`。

这是 K&R 时代就有的"位运算/比较运算"优先级陷阱。Clang/GCC 都会发 `-Wparentheses` 警告，但题目里没看到警告就容易翻车。

**来源：** cppquiz.org（多题考点）；C++17 [expr] 优先级表

## Explanation

正确答案是 B。
[expr]：C++ 中运算符优先级 == 高于 按位与 &。所以 a & b == c 等价于 a & (b == c)，不是 (a & b) == c。
b == c → 5 == 5 为 true，提升为 int(1)。
a & 1 → 6 & 1 = 0。
