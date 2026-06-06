---
qid: cpp-types-m-004
type: multi
kp: [cpp-types]
difficulty: easy
answer_key: [A, B, C]
---
以下哪些类型可以由 `auto` 正确推导？（选择所有正确项）

A. `auto x = 42;`（推导为 `int`）
B. `auto y = 3.14;`（推导为 `double`）
C. `auto z = 'A';`（推导为 `char`）
D. `auto w;`（不初始化，推导为 `void`）

## 解析

正确选项是 A（`auto x = 42;`（推导为 `int`））、B（`auto y = 3.14;`（推导为 `double`））、C（`auto z = 'A';`（推导为 `char`）），它们符合本题涉及的 C++ 规则。D（`auto w;`（不初始化，推导为 `void`）） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。类型题要关注值类别、cv 限定、隐式转换和推导规则；常见错误是忽略顶层/底层 const 或数组/函数退化。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
