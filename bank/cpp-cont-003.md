---
qid: cpp-cont-003
type: fill
kp: [cpp-containers]
difficulty: easy
answer_key: 不支持（list 不提供 operator[] 或 at()）
---

`std::list` 是双向链表，在已知迭代器处插入/删除的复杂度为 O(1)，但它 `______` 随机访问（即不能用 `operator[]` 按下标访问元素）。

## 解析

应填 `不支持（list 不提供 operator[] 或 at()）`。`std::list` 是双向链表，迭代器位置插入删除快，但不支持随机访问。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
