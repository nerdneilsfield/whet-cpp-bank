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
