---
qid: cpp-tmpl-adv-014
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

要用 `std::enable_if` 限制某个函数模板只接受整数类型，正确的写法是？

A.
```cpp
template<typename T>
void foo(T x) {
    static_assert(std::is_integral<T>::value, "must be integral");
}
```

B.
```cpp
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
foo(T x) { /* ... */ }
```

C.
```cpp
template<typename T>
void foo(T x) requires std::is_integral<T>::value { /* ... */ }
```

D. A 和 B 都正确，效果完全等价

> 注：A 是 `static_assert`（编译期断言，不走 SFINAE，调用错误类型时直接报错而非移除重载）；C 是 C++20 concepts 语法；B 是标准 SFINAE 写法，当 T 非整数时该重载被移除。

## Explanation

正确答案是 B，即 。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
