---
qid: cpp-cast-multi-002
type: multi
kp: [cpp-casting]
difficulty: medium
answer_key: [A, B, C]
---
关于 `dynamic_cast` 的前置条件与行为，**哪些说法是正确的**？（多选）

A. 类必须有至少一个虚函数（多态类型）。
B. 对指针转换失败返回 `nullptr`；对引用转换失败抛 `std::bad_cast`。
C. 在多重继承场景中，`dynamic_cast` 可正确处理跨子对象转换。
D. `dynamic_cast<void*>(p)` 返回 `p` 指向的最派生对象的字节起始地址，且无需 `p` 是多态类型。

---

**解析：**

A 正确：要求是多态类型。
B 正确：指针失败返回空，引用失败抛 `bad_cast`。
C 正确：能够处理多重/虚继承下的横向/交叉转换。
D 错误：`dynamic_cast<void*>` 仍要求源类型是多态的。