---
qid: cpp-stl-006
type: fill
kp: [cpp-stl-basics]
difficulty: easy
answer_key: "substr"
---

`std::string` 的 `._____( pos, len )` 成员函数用于提取从位置 `pos` 开始、长度为 `len` 的子串。

## 解析

填入 `substr`，因为题目要求的是该规则下的精确表达或标准名称。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
