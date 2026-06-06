---
qid: cpp-stl-adv-009
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# s.substr(pos, len) 用法与越界行为

```cpp
#include <string>

std::string s = "Hello, World!";
std::string sub = s.substr(7, 5);
```

关于 `s.substr(pos, len)`，以下哪条描述正确？

A. `sub` 的值为 `"Hello"`
B. `substr` 修改原字符串 `s`，截断为前 `len` 个字符
C. `sub` 的值为 `"World"`，若 `pos` 超过字符串长度则抛出 `std::out_of_range`
D. `len` 超出剩余长度时抛出异常

> **知识点**：`substr(pos, len)` 返回从 `pos` 起最多 `len` 个字符的新字符串，不修改原串。下标 7 对应 `'W'`，取 5 个字符得 `"World"`。`pos` 超界抛 `std::out_of_range`；`len` 超出剩余长度则安全截断至字符串末尾（不抛异常）。

## Explanation

正确答案是 C，即 `sub` 的值为 `"World"`，若 `pos` 超过字符串长度则抛出 `std::out_of_range`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
