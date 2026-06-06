---
qid: cpp-tmp-hard-002
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: C
---

以下代码实现了编译期类型列表的"取第 N 个类型"操作：

```cpp
template<int N, typename... Types>
struct TypeAt;

template<int N, typename Head, typename... Tail>
struct TypeAt<N, Head, Tail...> {
    using type = typename TypeAt<N - 1, Tail...>::type;
};

template<typename Head, typename... Tail>
struct TypeAt<0, Head, Tail...> {
    using type = Head;
};

using Result = TypeAt<2, int, double, char>::type;
```

`Result` 是什么类型？

A. `int`
B. `double`
C. `char`
D. 编译错误

## Explanation

正确答案是 C，即 `char`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
