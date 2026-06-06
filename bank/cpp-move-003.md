---
qid: cpp-move-003
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: A
---

# rvalue 引用语法

下列哪种声明是右值引用？

A. `int&& r = 5;`
B. `int& r = 5;`
C. `const int& r = 5;`
D. `int* r = &5;`

## Explanation

正确答案是 A，`int&&` 是右值引用类型，可以绑定到字面量 `5` 这样的右值。`int& r = 5` 不能把非常量左值引用绑定到右值；`const int&` 可以绑定临时量但类型是常量左值引用。`&5` 也非法，因为不能对纯右值字面量取地址。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
