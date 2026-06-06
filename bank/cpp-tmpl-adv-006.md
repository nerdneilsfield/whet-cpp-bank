---
qid: cpp-tmpl-adv-006
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

给定以下代码：

```cpp
#include <type_traits>
#include <iostream>

template <typename T>
void check(T val) {
    if constexpr (std::is_same<T, int>::value) {
        std::cout << "int branch\n";
    } else {
        std::cout << "other branch\n";
    }
}

int main() {
    check(3.14);
}
```

程序输出是？

A. `int branch`
B. `other branch`
C. 编译错误
D. 运行时未定义行为

## 解析

正确答案是 B，即 `other branch`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
