---
qid: cpp-stl-adv-012
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: D
---

# s.insert() 在指定位置插入字符串

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "Hello!";
    s.insert(5, ", World");
    std::cout << s << std::endl;
    return 0;
}
```

上述代码输出什么？

A. `Hello, World`
B. `, WorldHello!`
C. `Hello, World`（感叹号丢失）
D. `Hello, World!`

> **知识点**：`insert(pos, str)` 在下标 `pos` 处插入字符串 `str`，原下标 `pos` 及之后的字符向后移动。`"Hello!"` 下标 5 是 `'!'`，在它之前插入 `", World"`，结果为 `"Hello, World!"`。

## 解析

正确答案是 D，即 `Hello, World!`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
