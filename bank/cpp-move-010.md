---
qid: cpp-move-010
type: fill
kp: [cpp-move-semantics]
difficulty: easy
answer_key: "有效但未指定（valid but unspecified）"
---

# 移动后对象状态填空

C++ 标准规定，被移动（move-from）的对象处于 ______ 状态，可以安全地销毁或重新赋值，但不应假设其具体内容。

## Explanation

答案是“有效但未指定（valid but unspecified）”。被移动对象仍满足析构和赋值等基本要求，但其内部内容由实现和类型决定，不能依赖具体值。常见误区是认为移动后对象必为空，标准只保证它还处于可用的有效状态。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
