---
qid: cpp-tmpl-011
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

# 模板实例化结果

```cpp
template<typename T>
T square(T x) { return x * x; }

int a = square(3);
double b = square(2.5);
```

编译器会为上述代码生成几份 `square` 的实体（instantiation）？

A. 1 份，模板只有一份源码
B. 2 份，`square<int>` 和 `square<double>` 各一份
C. 4 份，每次调用生成一份
D. 0 份，模板在运行时动态解析

## 解析

正确答案是 B，即 2 份，`square<int>` 和 `square<double>` 各一份。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
