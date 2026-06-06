---
qid: cpp-cast-006
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: C
---

# C 风格转换等价

C 风格转换 `(T)expr` 会依次尝试多种 C++ 转换，其中**不包括**哪一种？

A. `static_cast`
B. `reinterpret_cast`
C. `dynamic_cast`
D. `const_cast`

## Explanation

正确答案是 C。C 风格转换会尝试 `const_cast`、`static_cast`、`reinterpret_cast` 及其组合，但不会执行 `dynamic_cast`。因此它不会做运行时类型检查，这也是 C++ 中推荐使用具名 cast 的原因。
