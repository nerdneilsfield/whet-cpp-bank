---
qid: cpp-ns-020
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: C
---

C++17 引入了哪种简化的嵌套命名空间写法？

A. `namespace Outer > Inner { }`
B. `namespace Outer.Inner { }`
C. `namespace Outer::Inner { }`
D. `namespace Outer, Inner { }`

## Explanation

正确答案是 C，因为该选项对应 ``namespace Outer::Inner { }``，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
