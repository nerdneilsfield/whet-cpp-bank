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

## 解析

正确选项是 A（`int` 的位宽（在不同平台上的大小）。）、C（`char` 是否是有符号类型。），它们符合本题涉及的 C++ 规则。B（解引用空指针的结果。）、D（越界访问 `std::vector` 的元素（通过 `operator[]`）。） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
