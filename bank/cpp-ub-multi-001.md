---
qid: cpp-ub-multi-001
type: multi
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: [A, B, D]
---
以下哪些场景是**未定义行为（UB）**？（多选）

A. 对空指针解引用。
B. 有符号整数溢出。
C. 无符号整数溢出。
D. 同一表达式中多次修改同一非原子变量且无 sequence point/order。

---

**解析：**

A 正确：解引用空指针是 UB。
B 正确：有符号整数溢出是 UB。
C 错误：无符号整数溢出是良定义行为（模 2^n）。
D 正确：在 C++17 前的旧规则下属 UB；C++17 起部分情形有 sequencing 但仍存在 UB 情形。