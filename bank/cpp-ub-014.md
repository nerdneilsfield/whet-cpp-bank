---
qid: cpp-ub-014
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# strict aliasing 简单例子

```cpp
int i = 0x3F800000;  // IEEE 754 表示 1.0f
float f = *(float*)&i;   // 通过 float* 读取 int 存储
```

上述代码（在非 `char*` 路径下）：

A. 保证合法，`int` 和 `float` 大小相同所以可以互转
B. 编译错误，C++ 不允许此类指针转型
C. 违反 strict aliasing 规则，属于未定义行为；正确做法是用 `memcpy` 或 `std::bit_cast`
D. 合法，只要结果在 `float` 的可表示范围内

## 解析

正确答案是 C，即 违反 strict aliasing 规则，属于未定义行为；正确做法是用 `memcpy` 或 `std::bit_cast`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
