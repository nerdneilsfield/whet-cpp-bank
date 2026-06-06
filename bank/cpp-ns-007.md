---
qid: cpp-ns-007
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

以下 `#if / #elif / #else` 代码最终打印什么？

```cpp
#define LEVEL 2

#if LEVEL == 1
    std::cout << "one";
#elif LEVEL == 2
    std::cout << "two";
#else
    std::cout << "other";
#endif
```

A. `one`
B. `two`
C. `other`
D. 编译错误

## 解析

正确答案是 B，因为该选项对应 ``two``，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
