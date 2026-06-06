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

## Explanation

应填 `CTAD`。CTAD 会根据构造实参推导类模板实参，省去显式写模板参数。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
