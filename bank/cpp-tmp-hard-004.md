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

## Explanation

填入 `3`，因为题目要求的是该规则下的精确表达或标准名称。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
