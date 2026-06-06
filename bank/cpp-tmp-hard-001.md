---
qid: cpp-tmp-hard-001
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: D
---

以下模板元编程代码在编译期计算 `2` 的 `N` 次方：

```cpp
template<int Base, int Exp>
struct Power {
    static constexpr int value = Base * Power<Base, Exp - 1>::value;
};

template<int Base>
struct Power<Base, 0> {
    static constexpr int value = 1;
};
```

`Power<2, 10>::value` 的值是？

A. 512
B. 256
C. 2048
D. 1024
