---
qid: cpp-ub-012
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: D
---

# 悬空引用

```cpp
#include <iostream>
int& get() {
    int local = 10;
    return local;   // 返回局部变量的引用
}
int main() {
    int& r = get();
    std::cout << r;
}
```

上述代码：

A. 编译错误，编译器禁止返回局部变量引用
B. 输出 10，局部变量在函数返回后仍有效
C. 运行时抛出异常，属于可预测错误
D. 未定义行为，`r` 是悬空引用，访问它后果不可预测

## Explanation

正确答案是 D，即 未定义行为，`r` 是悬空引用，访问它后果不可预测。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
