---
qid: cpp-tmpl-020
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "int[10]（data 是 int[10] 类型的数组）"
---

# 非类型模板参数与数组

```cpp
template<typename T, int N>
struct Array {
    T data[N];
};

Array<int, 10> a;
```

`a.data` 的类型是 ___。

## 解析

填入 `int[10]（data 是 int[10] 类型的数组）`，因为题目要求的是该规则下的精确表达或标准名称。指针、数组和引用题要注意数组到指针退化、指针算术按元素大小推进，以及引用绑定后只是对象别名。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
