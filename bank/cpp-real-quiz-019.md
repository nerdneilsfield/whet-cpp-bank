---
qid: cpp-real-quiz-019
type: single
kp: [cpp-operators]
primary_kp: cpp-operators
difficulty: medium
answer_key: A
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的输出是？

```cpp
#include <iostream>
int main() {
    int i = 0;
    std::cout << (i++, i + 10, i) << ' ';
    std::cout << (i += 10, i * 2, i);
}
```

A. `1 11`
B. `10 20`
C. `10 21`
D. `11 11`

---

**解析：**

**逗号运算符** `expr1, expr2` 依次求值 expr1、expr2，返回**最右侧表达式**的结果（[expr.comma]/1）。

第一行：`(i++, i + 10, i)`
- `i++` → i 变成 1
- `i + 10` → 结果是 11，丢弃
- `i` → 结果是 1（当前 i 值）
输出 `1`。

第二行：`(i += 10, i * 2, i)`
- `i += 10` → i 变成 11
- `i * 2` → 结果是 22，丢弃
- `i` → 结果是 11
输出 `11`。

易混淆答案：以为逗号表达式最终返回 i * 2 或 i += 10 的结果——实际上返回的是**最后一个子表达式**。

**来源：** C++17 [expr.comma]/1