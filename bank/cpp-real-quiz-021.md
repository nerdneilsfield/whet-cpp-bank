---
qid: cpp-real-quiz-021
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
    (a = b) = c;
    std::cout << a << ' ' << b << ' ' << c;
}
```

A. `3 2 3`
B. `2 2 3`
C. 编译错误
D. 行为未定义

---

**解析：**

[expr.ass]/1：内建类型的赋值表达式 `a = b` 的结果是**对 a 的 lvalue 引用**（注意 C 中是 rvalue）。所以 `(a = b)` 返回 `a` 的 lvalue，可以继续被赋值。

求值顺序（C++17 起明确保证）：
1. 右侧 `c` 先求值（值 3）
2. 然后内层 `a = b`：`a` 变 `2`，返回 `a` 的 lvalue
3. 外层 `(a) = c`：`a` 变 `3`

最终 `a = 3`，`b = 2`，`c = 3`。

C++17 之前求值顺序未指定，链式赋值的中间副作用可能 UB；C++17 起 `=` 的求值顺序明确为右先左后，且各 side-effect 有序，本式 well-defined。

**来源：** C++17 [expr.ass]/1（与 P0145R3 求值顺序提案）

## Explanation

正确答案是 A。
[expr.ass]/1：内建类型的赋值表达式 a = b 的结果是对 a 的 lvalue 引用（注意 C 中是 rvalue）。所以 (a = b) 返回 a 的 lvalue，可以继续被赋值。
求值顺序（C++17 起明确保证）： 右侧 c 先求值（值 3） 然后内层 a = b：a 变 2，返回 a 的 lvalue 外层 (a) = c：a 变 3 最终 a = 3，b = 2，c = 3。
C++17 之前求值顺序未指定，链式赋值的中间副作用可能 UB；C++17 起 = 的求值顺序明确为右先左后，且各 side-effect 有序，本式 well-defined。
