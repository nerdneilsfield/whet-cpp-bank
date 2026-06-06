---
qid: cpp-cont-007
type: fill
kp: [cpp-containers]
difficulty: easy
answer_key: push_front / push_back
---

`std::deque` 支持在两端以 O(1) 复杂度插入元素，对应的成员函数分别是 `______` 和 `______`。

## 解析

应填 `push_front / push_back`。`std::deque` 支持两端高效插入删除，但迭代器稳定性不同于 `list`。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
