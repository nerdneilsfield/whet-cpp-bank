---
qid: cpp-opov-fill-med-001
type: fill
kp: [cpp-operator-overload]
difficulty: medium
answer_key: "<=>"
---
C++20 三路比较运算符是 ___。

---

**解析：**

`<=>`（spaceship operator）是 C++20 引入的三路比较运算符，返回 `std::strong_ordering`、`std::weak_ordering` 或 `std::partial_ordering` 之一。编译器可自动生成 `==`、`!=`、`<`、`<=`、`>`、`>=` 六个关系运算符（通过 `= default` 声明），极大简化自定义类型比较的样板代码。

## Explanation

填空应为 `<=>`，因为这是题干所问概念或语法在 C++ 中的标准写法。运算符重载题要区分语法形式与实际调用的函数，并注意返回值、const、成员/非成员选择及内置运算符语义限制。常见误区是把重载看成改变了语言规则，或忽略临时对象、引用返回和左右操作数类型对重载解析的影响。 常见误区是写出近似术语、别名或只写部分符号；填空题通常要求与答案键精确对应。
