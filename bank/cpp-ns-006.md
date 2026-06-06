---
qid: cpp-ns-006
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: D
---

以下代码中，`hello()` 会被调用吗？

```cpp
#define DEBUG 0

#ifdef DEBUG
    hello();
#endif
```

A. 会，因为 `DEBUG` 已经被定义
B. 不会，因为 `DEBUG` 的值为 0（假）
C. 编译报错，`#ifdef` 不能检测值为 0 的宏
D. 会，`#ifdef` 只检查宏是否被定义，不看值；但此处 `DEBUG` 确实已定义，所以 `hello()` 会被编译进去

## Explanation

正确答案是 D，因为该选项对应 `会，`#ifdef` 只检查宏是否被定义，不看值；但此处 `DEBUG` 确实已定义，所以 `hello()` 会被编译进去`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、B 项、C 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
