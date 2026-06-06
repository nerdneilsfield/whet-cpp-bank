---
qid: cpp-types-m-002
type: multi
kp: [cpp-types]
difficulty: easy
answer_key: [B, C]
---
以下哪些初始化方式会发生窄化转换（narrowing conversion）？（选择所有正确项）

A. `int x{42};`
B. `int y{3.14};`
C. `char c{300};`
D. `double d{1.0f};`

## 解析

正确选项是 B（`int y{3.14};`）、C（`char c{300};`），它们符合本题涉及的 C++ 规则。A（`int x{42};`）、D（`double d{1.0f};`） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。类型题要关注值类别、cv 限定、隐式转换和推导规则；常见错误是忽略顶层/底层 const 或数组/函数退化。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
