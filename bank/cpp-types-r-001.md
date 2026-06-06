---
qid: cpp-types-r-001
type: single
kp: [cpp-types]
difficulty: easy
answer_key: B
---

# 代码阅读：auto 推导 initializer_list

下列代码能否编译？若能，`x` 的类型是什么？

```cpp
#include <initializer_list>
auto x = {1, 2, 3};
```

A. 编译错误：无法从花括号列表推导 `auto`  
B. 编译成功；`x` 的类型是 `std::initializer_list<int>`  
C. 编译成功；`x` 的类型是 `int[3]`  
D. 编译成功；`x` 的类型是 `std::vector<int>`

## 解析

正确答案是 B，即 编译成功；`x` 的类型是 `std::initializer_list<int>`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
