---
qid: cpp-real-quiz-004
type: single
kp: [cpp-operators]
primary_kp: cpp-operators
difficulty: hard
answer_key: B
tags: [interview-real, cppquiz, language-lawyer]
---
根据 C++17 标准，以下程序的行为是？

```cpp
#include <iostream>
int main() {
    std::cout << (-7 / 2) << ' ' << (-7 % 2);
}
```

A. 输出 `-4 -1`
B. 输出 `-3 -1`
C. 输出 `-4 1`
D. 行为未指定（实现定义）

---

**解析：**

C++11 之前，负整数除法与取模的商如何处理（向零截断还是向下取整）是**实现定义行为**。C++11 起，[expr.mul]/4 明确规定：**商向零截断（truncation toward zero）**，即 `-7 / 2 = -3`（不是 -4）。

取模满足恒等式 `(a/b)*b + a%b == a`：`-3 * 2 + (-1) == -7`，所以 `-7 % 2 = -1`。

易混淆答案 A (-4 -1) 对应的是被 Python 等语言采用的"floor division" 策略（向负无穷取整）。C++ 坚持向零截断。

**来源：** C++17 [expr.mul]/4；C++11 CU（core issue 1459 前有争议）