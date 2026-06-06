---
qid: cpp-real-ali-009
type: single
kp: [cpp-casting]
primary_kp: cpp-casting
difficulty: medium
answer_key: A
tags: [interview-real, alibaba]
---
在以下哪种场景下，必须使用 `dynamic_cast` 而不是 `static_cast`？

A. 将基类指针向下转换为派生类指针，且基类不是多态类型（无虚函数）
B. 将基类指针向下转换为派生类指针，且基类是多态类型（有虚函数），转换的安全性需要在运行时检查
C. 将 `int*` 转换为 `char*`
D. 去掉对象的 `const` 限定

---

**解析：**

选 B。C++ 四种 cast 的选用场景：

| cast | 场景 | 说明 |
|------|------|------|
| `static_cast` | 编译期已知安全的转换 | 隐式转换逆、void*←→T*、向上转换、无多态的向下转换 |
| `dynamic_cast` | 运行时安全检查的向下/侧向转换 | **必须有虚函数表的类型**，失败返回 nullptr（指针）或抛 bad_cast（引用） |
| `const_cast` | 增加/去除 const/volatile | 唯一能做这件事的 cast |
| `reinterpret_cast` | 底层的位模式重解释 | 最危险，如 float→int 按位读，必须确保类型兼容 |

**为什么 dynamic_cast 必须要求虚函数？** 因为它依赖于 vtable 中的 RTTI 信息。如果基类没有虚函数，类就没有 vtable，dynamic_cast 无法做运行时类型检查。

A 错：基类没有虚函数，dynamic_cast 编译错误。
C 错：static_cast 或 reinterpret_cast 都可以（后者更"明显表示不安全"）。
D 错：const_cast 才是做这个的。

**来源：** 阿里 C++ 后端面试追问（参考：Effective C++ Item 27、cppreference）

## Explanation

正确答案是 A。
A 错：基类没有虚函数，dynamic_cast 编译错误。
