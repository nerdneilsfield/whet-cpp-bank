---
qid: cpp-tmpl-007
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "double"
---

# 显式模板参数

```cpp
template<typename T>
T add(T a, T b) { return a + b; }

auto result = add<double>(3, 5);
```

`result` 的类型是 ___。

## Explanation

填入 `double`，因为题目要求的是该规则下的精确表达或标准名称。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
