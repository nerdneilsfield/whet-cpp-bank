---
qid: cpp-cont-008
type: fill
kp: [cpp-containers]
difficulty: easy
answer_key: find
---

`std::map` 中，若要查找键是否存在且**不希望插入默认值**，应使用 `______` 成员函数而非 `operator[]`。

## 解析

应填 `find`。`std::map` 通常由平衡二叉搜索树实现，键有序，查找/插入/删除为 O(log n)。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
