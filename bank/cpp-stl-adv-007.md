---
qid: cpp-stl-adv-007
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# s.find() 找不到时的返回值

```cpp
#include <string>
#include <iostream>

std::string s = "hello world";
auto pos = s.find("xyz");
```

当 `find()` 找不到目标子串时，返回值是什么？

A. 返回 `-1`
B. 返回 `std::string::npos`，其值等于 `size_t` 类型的最大值
C. 返回 `0`
D. 抛出 `std::runtime_error` 异常

> **知识点**：`std::string::find()` 找不到时返回 `std::string::npos`，其定义为 `static const size_type npos = -1`（无符号类型，实际值是 `size_t` 的最大值，通常为 `18446744073709551615` 在 64 位系统上）。常见判断写法：`if (pos == std::string::npos)`。

## 解析

正确答案是 B，即 返回 `std::string::npos`，其值等于 `size_t` 类型的最大值。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
