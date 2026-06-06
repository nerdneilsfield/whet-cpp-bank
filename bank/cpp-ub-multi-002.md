---
qid: cpp-ub-multi-002
type: multi
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: [A, C]
---
以下哪些属于**实现定义行为（implementation-defined）**？（多选）

A. `int` 的位宽（在不同平台上的大小）。
B. 解引用空指针的结果。
C. `char` 是否是有符号类型。
D. 越界访问 `std::vector` 的元素（通过 `operator[]`）。

---

**解析：**

A 正确：基本类型大小是实现定义的。
B 错误：解引用空指针是 UB。
C 正确：`char` 默认是 signed 还是 unsigned 是实现定义的。
D 错误：`operator[]` 越界是 UB，不是实现定义。