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