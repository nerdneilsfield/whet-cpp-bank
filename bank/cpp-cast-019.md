---
qid: cpp-cast-019
type: multi
kp: [cpp-casting]
difficulty: easy
answer_key: [A, C, D]
---

# C 风格转换的隐患

相比具名 C++ 转换，C 风格转换 `(T)x` 的隐患包括哪些？（多选）

A. 可能静默地去除 `const`，难以察觉
B. 只能调用 `static_cast`，功能有限
C. 搜索代码时难以用正则快速定位所有类型转换
D. 可能静默地触发 `reinterpret_cast` 语义，产生危险行为
