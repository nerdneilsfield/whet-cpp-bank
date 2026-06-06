---
qid: cpp-ub-005
type: multi
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: [B, D]
---

# strict aliasing 违规场景（多选）

下列哪些情况**可能违反 strict aliasing 规则**，属于未定义行为？（多选）

A. 通过 `char*` 读取任意类型对象的字节
B. 通过 `float*` 读取一块存储 `int` 值的内存
C. 通过 `void*` 传递指针再转回原始类型使用
D. 用 `int*` 解引用一块实际存储 `double` 的内存
E. 通过 `unsigned char*` 遍历 `struct` 的字节
