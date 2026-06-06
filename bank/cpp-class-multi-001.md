---
qid: cpp-class-multi-001
type: multi
kp: [cpp-classes]
difficulty: medium
answer_key: [A, D]
---
关于 const 成员函数，**哪些说法是正确的**？（多选）

A. const 成员函数内部不能直接修改对象的非 static 数据成员。
B. const 成员函数内部不能调用任何非 const 成员函数。
C. const 成员函数不能返回对数据成员的引用。
D. `mutable` 关键字可以在 const 成员函数中修改特定成员。

---

**解析：**

A 正确：const 成员函数中 `*this` 是 const 的，因此不能修改普通数据成员。
B 错误：可以调用另一个 const 成员函数，但不能调用非 const 成员函数。
C 错误：可以返回对数据成员的 `const` 引用；若返回非 const 引用则编译器报错。
D 正确：`mutable` 专门用于声明在 const 上下文中仍可修改的成员（如缓存、锁等）。