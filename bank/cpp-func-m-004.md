---
qid: cpp-func-m-004
type: multi
kp: [cpp-functions]
difficulty: easy
answer_key: [A, C, D]
---

关于 C++ **`inline` 函数**，选择所有正确项。

```cpp
inline int square(int x) {
    return x * x;
}
```

A. `inline` 是对编译器的建议，编译器可以忽略该请求
B. `inline` 函数保证每次调用都被展开，消除函数调用开销
C. `inline` 函数通常定义在头文件中，以便多个翻译单元使用
D. `inline` 函数在多个翻译单元中定义时，所有定义必须完全相同

> 选择所有正确项。
