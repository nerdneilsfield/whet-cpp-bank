---
qid: cpp-tmp-hard-001
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: D
---

以下模板元编程代码在编译期计算 `2` 的 `N` 次方：

```cpp
template<int Base, int Exp>
struct Power {
    static constexpr int value = Base * Power<Base, Exp - 1>::value;
};

template<int Base>
struct Power<Base, 0> {
    static constexpr int value = 1;
};
```

`Power<2, 10>::value` 的值是？

A. 512
B. 256
C. 2048
D. 1024

## 解析

正确答案是 D，即 1024。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
