---
qid: cpp-ub-015
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# 移动后继续使用

```cpp
#include <string>
#include <iostream>
int main() {
    std::string s = "hello";
    std::string t = std::move(s);
    std::cout << s.size();  // 使用被移走的 s
}
```

上述代码的行为是：

A. 未定义行为：被 `std::move` 后，`s` 处于"有效但未指定"状态，读取其内容结果不可预测
B. 编译错误：移动后不允许访问原对象
C. 输出 5，`std::move` 只是语义标记，不实际移动数据
D. 确定输出 0，标准规定移动后 `size()` 为 0

## 解析

正确答案是 A，即 未定义行为：被 `std::move` 后，`s` 处于"有效但未指定"状态，读取其内容结果不可预测。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
