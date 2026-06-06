---
qid: cpp-cast-001
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

# static_cast 用途

下列哪种场景最适合使用 `static_cast`？

A. 将 `const int*` 转为 `int*`
B. 将 `double` 转为 `int`
C. 将基类指针安全地转为派生类指针（有虚函数）
D. 将 `int*` 重新解释为 `char*`

## Explanation

正确答案是 B。`static_cast` 适合做编译期可检查的常规类型转换，例如数值类型之间的转换、相关指针/引用的上行转换等。去除 `const` 应使用 `const_cast`，运行时安全向下转型应使用 `dynamic_cast`，按位重新解释指针应使用 `reinterpret_cast`。
