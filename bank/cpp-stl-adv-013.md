---
qid: cpp-stl-adv-013
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# s.compare() 的返回值语义

```cpp
#include <string>

std::string a = "apple";
std::string b = "banana";
int result = a.compare(b);
```

关于 `compare()` 的返回值，以下说法正确的是？

A. 返回 `true` 或 `false`
B. 返回值为 1、0 或 -1，含义固定
C. 返回 0 表示相等，负数表示调用者小于参数，正数表示调用者大于参数
D. `"apple".compare("banana")` 返回正数，因为 apple 字母更少

> **知识点**：`compare()` 按字典序比较，返回：0（相等）、负数（调用者 < 参数）、正数（调用者 > 参数）。具体值不保证是 -1/1，只保证符号。`'a' < 'b'`，所以 `"apple".compare("banana")` 返回负数。

## Explanation

正确答案是 C，即 返回 0 表示相等，负数表示调用者小于参数，正数表示调用者大于参数。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
