---
qid: cpp-cast-015
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: D
---

# void* 转回具体指针

将 `void*` 转换回原始类型指针，应使用哪种 C++ 转换？

A. `dynamic_cast`
B. `const_cast`
C. `reinterpret_cast`
D. `static_cast`

## 解析

正确答案为 D，因为“`static_cast`”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
