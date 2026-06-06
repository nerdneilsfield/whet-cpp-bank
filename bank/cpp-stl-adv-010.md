---
qid: cpp-stl-adv-010
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# s.replace() 替换子串

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "I like cats";
    s.replace(7, 4, "dogs");
    std::cout << s << std::endl;
    return 0;
}
```

上述代码输出什么？

A. `I like cats dogs`
B. `I like dogs`
C. `I like dogscats`
D. `I like cat`

> **知识点**：`replace(pos, len, str)` 将从 `pos` 开始的 `len` 个字符替换为 `str`，并修改原字符串。`"I like cats"` 中下标 7 是 `'c'`，`len=4` 覆盖 `"cats"`，替换为 `"dogs"`，结果为 `"I like dogs"`。

## 解析

正确答案是 B，即 `I like dogs`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
