---
qid: cpp-exc-007
type: fill
kp: [cpp-exceptions]
difficulty: easy
answer_key: "what()"
---

# C++ 异常处理：std::exception 接口

`std::exception` 提供的虚函数，用于返回异常描述字符串的方法名是 ______。

## Explanation

应填 `what()`。标准异常层次通常以 `std::exception` 为公共基类，并通过 `what()` 返回说明。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
