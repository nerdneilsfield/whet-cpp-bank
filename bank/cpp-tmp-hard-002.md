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
