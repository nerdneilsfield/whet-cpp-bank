---
qid: cpp-tmpl-adv-009
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: A
---

以下用可变参数模板递归展开的 `print` 函数，正确的实现模式是？

A.
```cpp
void print() {}  // 递归终止：空参数包

template<typename T, typename... Rest>
void print(T first, Rest... rest) {
    std::cout << first << "\n";
    print(rest...);  // 递归展开
}
```

B.
```cpp
template<typename... Args>
void print(Args... args) {
    std::cout << args << "\n";  // 直接展开，不递归
}
```

C.
```cpp
template<typename... Args>
void print(Args... args) {
    for (auto a : args) std::cout << a << "\n";  // range-for 展开
}
```

D.
```cpp
template<typename T>
void print(T first, T... rest) {  // 所有参数必须同类型
    std::cout << first;
    print(rest...);
}
```

## Explanation

正确答案是 A，即 。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
