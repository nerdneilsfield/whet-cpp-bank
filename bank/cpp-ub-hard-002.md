---
qid: cpp-ub-hard-002
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: D
---

以下代码的输出或行为是什么？

```cpp
#include <iostream>
const int& f(int x) { return x; }

int main() {
    const int& r = f(42);
    std::cout << r;  // ?
}
```

A. 打印 `42`，因为 C++ 保证局部对象的生命期被引用延长
B. 编译失败：不能返回局部引用
C. 打印随机值
D. 未定义行为：函数参数 `x` 是局部临时，返回引用挂回它；虽然 `const int&` 绑定到表达式的生命周期延长规则**不**适用于函数返回值绑定——临时在函数返回后销毁，`r` 悬垂

## 解析

C++ 生命周期延长规则对比：
- `const auto& x = expr;` 中若 `expr` 生成临时对象，其生命周期被扩展到引用作用域结束——这是正确的延长。
- 但 `f(42)` 返回的 `const int&` 绑定到 `f` 内的参数 `x`（一个局部变量）。它的生命周期在 `f` 返回时结束。即使外部用 `const int& r` 捕获该引用，也**不会再**被延长——规则仅适用于**纯右值表达式**直接绑定到引用的场景，不适用于跨函数调用链返回的引用。

因此 `r` 是悬垂引用，读取它是 UB。输出可能看似对（栈未被覆盖时），但仍属 UB。C++ 这一定位设计上是合理的：不同编译器优化程度下行为差异大。