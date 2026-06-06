---
qid: cpp-tmpl-med-003
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---
下列代码涉及两阶段名字查找，`d.f()` 调用结果是？

```cpp
#include <iostream>
void g() { std::cout << "global g"; }
template<typename T>
struct Base { void g() { std::cout << "Base g"; } };
template<typename T>
struct Derived : Base<T> {
    void f() { g(); }
};
int main() {
    Derived<int> d;
    d.f();
    return 0;
}
```

A. 输出 "Base g"
B. 输出 "global g"
C. 编译错误
D. 未定义行为

---

**解析：**

模板的两阶段名字查找：第一阶段（模板定义时）对**非依赖名**做常规查找；第二阶段（实例化时）才查找依赖名。`f()` 中的 `g()` 不依赖模板参数 `T`，因此在定义阶段就被解析。此时基类模板 `Base<T>` 尚未实例化，它内部的 `g` 不可见，于是只能找到全局 `g`，绑定为 `::g`。即使后来实例化 `Derived<int>`，调用结果仍是全局 `g`。要使用基类成员，必须写 `this->g()` 或 `Base<T>::g()` 把名字变成依赖名。

## Explanation

正确答案是 B，即 输出 "global g"。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
