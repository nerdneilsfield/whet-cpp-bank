---
qid: cpp-stl-fill-med-001
type: fill
kp: [cpp-stl-basics]
difficulty: medium
answer_key: "SSO"
---
`string` 内部小字符串优化的英文缩写是 ___。

---

**解析：**

SSO（Small String Optimization / Short String Optimization）是 `std::string` 的常见实现优化策略：对于长度较短的字符串，直接存储在对象内部的静态缓冲区中，而非动态分配堆内存。具体阈值因实现而异（通常 15–22 字符），但 SSO 可显著减少小字符串场景下的堆分配开销。

## Explanation

填入 `SSO`，因为题目要求的是该规则下的精确表达或标准名称。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
