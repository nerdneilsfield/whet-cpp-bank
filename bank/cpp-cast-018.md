---
qid: cpp-cast-018
type: multi
kp: [cpp-casting]
difficulty: easy
answer_key: [B, D]
---

# 哪些转换需要 dynamic_cast

下列场景中，哪些**必须**（或最应）使用 `dynamic_cast`？（多选）

A. 将 `int` 转为 `long`
B. 在运行时安全地将基类指针向下转型为派生类指针
C. 去除函数参数的 `const` 限定以传给旧接口
D. 在多重继承中进行侧向转型（cross-cast）
