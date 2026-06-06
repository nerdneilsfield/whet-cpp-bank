---
qid: cpp-types-m-006
type: multi
kp: [cpp-types]
difficulty: easy
answer_key: [A, C, D]
---
关于 `sizeof` 运算符，以下哪些说法正确？（选择所有正确项）

A. `sizeof` 的返回类型是 `size_t`（无符号整数类型）
B. `sizeof(int)` 在所有平台上固定返回 4
C. `sizeof` 是编译期求值的，不会在运行时产生函数调用
D. `sizeof` 可以作用于类型名，也可以作用于表达式

## 解析

正确选项是 A（`sizeof` 的返回类型是 `size_t`（无符号整数类型））、C（`sizeof` 是编译期求值的，不会在运行时产生函数调用）、D（`sizeof` 可以作用于类型名，也可以作用于表达式），它们符合本题涉及的 C++ 规则。B（`sizeof(int)` 在所有平台上固定返回 4） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。大小相关题要分清 C++ 标准保证、平台 ABI 约定和对象表示；`sizeof` 结果以字节计，类型为 `size_t`。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
