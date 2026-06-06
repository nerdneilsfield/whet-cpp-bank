---
qid: cpp-cpp17-fill-med-001
type: fill
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: "CTAD"
---
C++17 类模板参数推导简称 ___。

---

**解析：**

CTAD（Class Template Argument Deduction，类模板参数推导）是 C++17 特性，允许编译器从构造函数实参推导类模板参数。例如 `std::pair p(1, 2.0)` 自动推导为 `std::pair<int, double>`。CTAD 依赖推导指引（deduction guides）处理复杂的构造函数模板情形。