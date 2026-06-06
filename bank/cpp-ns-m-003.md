---
qid: cpp-ns-m-003
type: multi
kp: [cpp-preprocessor]
difficulty: easy
answer_key: [A, C, D]
---

关于 C++ `namespace`，下列哪些说法**正确**？（选择所有正确项）

A. 同一命名空间可以在多个文件中分散定义，编译器会将其合并
B. 命名空间只能定义在全局作用域，不能嵌套
C. 可以使用 `namespace Alias = LongNamespaceName;` 为命名空间创建别名
D. 命名空间内的函数可以通过 `::` 限定符（如 `MyNS::foo()`）在外部调用

## Explanation

正确答案是 A, C, D。A 项 `同一命名空间可以在多个文件中分散定义，编译器会将其合并` 符合规则；C 项 `可以使用 `namespace Alias = LongNamespaceName;` 为命名空间创建别名` 符合规则；D 项 `命名空间内的函数可以通过 `::` 限定符（如 `MyNS::foo()`）在外部调用` 符合规则；B 项 `命名空间只能定义在全局作用域，不能嵌套` 不满足该规则。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 多选题常见误区是只看关键字相似就勾选，而没有逐项检查它是否真的满足题干条件。
