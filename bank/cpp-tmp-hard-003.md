---
qid: cpp-tmp-hard-003
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

以下代码试图递归计算阶乘，但存在问题：

```cpp
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// 缺少终止特化

int main() {
    int x = Factorial<5>::value;
}
```

编译该代码会发生什么？

A. 正常编译，`x = 120`
B. 编译失败，因为模板递归无终止条件，实例化无限展开
C. 运行时崩溃，栈溢出
D. `x = 0`，因为编译器自动将负数实例化截断

## Explanation

正确答案是 B，即 编译失败，因为模板递归无终止条件，实例化无限展开。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
