---
qid: cpp-types-r-005
type: single
kp: [cpp-types]
difficulty: easy
answer_key: C
---

# 代码阅读：constexpr 在运行时使用

```cpp
#include <iostream>
constexpr int square(int n) { return n * n; }

int main() {
    int x;
    std::cin >> x;
    std::cout << square(x) << "\n";
}
```

以下说法哪个**正确**？

A. 编译错误：`constexpr` 函数不能接收运行时参数  
B. 编译错误：`square(x)` 必须在编译期求值  
C. 编译成功，运行时正常输出 `x` 的平方；`constexpr` 函数在参数非常量时退化为普通函数  
D. 编译成功，但 `square(x)` 始终返回 `0`（运行时未计算）

## 解析

正确答案是 C，即 编译成功，运行时正常输出 `x` 的平方；`constexpr` 函数在参数非常量时退化为普通函数。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。类型题要关注值类别、cv 限定、隐式转换和推导规则；常见错误是忽略顶层/底层 const 或数组/函数退化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
