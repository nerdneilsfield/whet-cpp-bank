---
qid: cpp-real-quiz-020
type: single
kp: [cpp-operators]
primary_kp: cpp-operators
difficulty: hard
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
int main() {
    int a = 1, b = 2, c = 3;
    (a < b ? a : b) = c;     // (1)
    std::cout << a << ' ' << b;
}
```

A. 输出 `3 2`
B. 输出 `1 3`
C. 编译错误（三元表达式不是 lvalue）
D. 行为未定义

---

**解析：**

[expr.cond]：三元表达式 `a ? b : c` 的值类别由 b 和 c 决定。当 **b 和 c 类型相同且都是 lvalue** 时，整个三元表达式也是 **lvalue**（且类型为公共类型）。

`a < b` 为 true，所以三元表达式选 `a`；它是 lvalue，可以作为赋值目标，于是 `a = c` → `a = 3`。`b` 不变保持 `2`。

输出 `3 2`。

易混淆答案 C：很多 C 程序员以为 `a ? b : c` 永远是右值（在 C 里确实是），但在 C++ 里只要两边类型/值类别匹配，整体可作 lvalue 使用。

**来源：** cppquiz.org（多题）；C++17 [expr.cond]/5

## Explanation

正确答案是 A。
[expr.cond]：三元表达式 a ? b : c 的值类别由 b 和 c 决定；当 b 和 c 类型相同且都是 lvalue 时，整个三元表达式也是 lvalue（且类型为公共类型）。
a < b 为 true，所以三元表达式选 a；它是 lvalue，可以作为赋值目标，于是 a = c → a = 3；b 不变保持 2。
输出 3 2。
