---
qid: cpp-tmp-hard-004
type: fill
kp: [cpp-templates]
difficulty: hard
answer_key: 3
---

以下代码定义了一个类型列表并在编译期计算其长度：

```cpp
template<typename... Types>
struct TypeList {};

template<typename List>
struct Length;

template<typename... Types>
struct Length<TypeList<Types...>> {
    static constexpr int value = sizeof...(Types);
};

constexpr int N = Length<TypeList<int, double, char>>::value;
```

`N` 的值是 ___。
