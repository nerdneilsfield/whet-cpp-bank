---
qid: cpp-cont-005
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: B
---

`std::stack` 默认使用哪个底层容器实现？

A. `std::vector`
B. `std::deque`
C. `std::list`
D. `std::array`

## Explanation

正确答案是 B。`std::list` 是双向链表，迭代器位置插入删除快，但不支持随机访问。选项 B 的表述“｀std::deque｀”正好符合该规则。A、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。 进一步判断时要回到题干给出的具体代码、接口名和标准语义，避免用相似概念的经验结论替代本题要求。
