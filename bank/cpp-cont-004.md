---
qid: cpp-cont-004
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: D
---

`std::priority_queue` 的 `top()` 默认返回什么？

A. 最小元素
B. 最近插入的元素
C. 最先插入的元素
D. 最大元素

## 解析

正确答案是 D。`std::priority_queue` 默认是最大堆，`top()` 返回当前最大元素。选项 D 的表述“最大元素”正好符合该规则。A、B、C 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
