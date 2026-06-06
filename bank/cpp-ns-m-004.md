---
qid: cpp-ns-m-004
type: multi
kp: [cpp-preprocessor]
difficulty: easy
answer_key: [A, B, D]
---

下列哪些是**合法的 C++ 预处理指令**？（选择所有正确项）

A. `#include <vector>`
B. `#if defined(DEBUG) && !defined(NDEBUG)`
C. `#namespace std`
D. `#error "不支持该平台"`

## 解析

正确答案是 A, B, D。A 项 ``#include <vector>`` 符合规则；B 项 ``#if defined(DEBUG) && !defined(NDEBUG)`` 符合规则；D 项 ``#error "不支持该平台"`` 符合规则；C 项 ``#namespace std`` 不满足该规则。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
