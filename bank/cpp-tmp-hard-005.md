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
