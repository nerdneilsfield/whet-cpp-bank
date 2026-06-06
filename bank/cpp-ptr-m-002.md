---
qid: cpp-ptr-m-002
type: multi
kp: [cpp-arrays-pointers]
difficulty: easy
answer_key: [B, C, D]
---

下列关于指针与 `nullptr` 的说法，哪些是正确的？（选择所有正确项）

A. 指针变量声明后若未初始化，其值为 `nullptr`
B. 解引用 `nullptr` 指针会导致未定义行为
C. `nullptr` 的类型是 `std::nullptr_t`，可隐式转换为任意指针类型
D. 可以用 `if (p)` 判断指针 `p` 是否为空

## 解析

正确选项是 B（解引用 `nullptr` 指针会导致未定义行为）、C（`nullptr` 的类型是 `std::nullptr_t`，可隐式转换为任意指针类型）、D（可以用 `if (p)` 判断指针 `p` 是否为空），它们符合本题涉及的 C++ 规则。A（指针变量声明后若未初始化，其值为 `nullptr`） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
