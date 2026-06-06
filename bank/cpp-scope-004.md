---
qid: cpp-scope-004
type: single
kp: [cpp-scope-linkage]
difficulty: easy
answer_key: D
---

# const 全局变量的默认链接性

在 C++ 中，以下哪条关于文件作用域 `const` 变量的说法**正确**？

A. 默认具有外部链接，其他文件可以 `extern` 引用
B. 默认具有内部链接，但可以用 `extern const` 改为外部链接
C. 与非 `const` 全局变量完全相同，默认外部链接
D. 默认具有内部链接，等价于加了 `static`

> 提示：B 和 D 表述相近——注意 B 说"可以改为外部链接"，D 是正确完整描述。
