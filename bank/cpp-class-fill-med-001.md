---
qid: cpp-class-fill-med-001
type: fill
kp: [cpp-classes]
difficulty: medium
answer_key: "mutable"
---
允许 `const` 成员函数修改的成员需要标 ___ 关键字。

---

**解析：**

`mutable` 用于声明即使在 `const` 成员函数中也可被修改的非静态数据成员。典型用途包括互斥锁、缓存标志、引用计数等逻辑上不改变"外部可见状态"的内部变量。`mutable` 不能用于静态或引用成员。