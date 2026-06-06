---
qid: cpp-tmpl-018
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "编译错误（N 必须是编译期常量，不能是运行时变量）"
---

# 非类型模板参数约束

```cpp
template<int N>
struct FixedArray {
    int data[N];
};

int size = 10;
FixedArray<size> arr;
```

上述代码的编译结果是：___。

## 解析

填入 `编译错误（N 必须是编译期常量，不能是运行时变量）`，因为题目要求的是该规则下的精确表达或标准名称。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
