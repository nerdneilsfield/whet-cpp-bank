---
qid: cpp-tmp-hard-005
type: fill
kp: [cpp-templates]
difficulty: hard
answer_key: 15
---

以下代码在编译期递归求和：

```cpp
template<int First, int... Rest>
struct Sum {
    static constexpr int value = First + Sum<Rest...>::value;
};

template<int Last>
struct Sum<Last> {
    static constexpr int value = Last;
};

constexpr int result = Sum<1, 2, 3, 4, 5>::value;
```

`result` 的值是 ___。

## Explanation

填入 `15`，因为题目要求的是该规则下的精确表达或标准名称。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
