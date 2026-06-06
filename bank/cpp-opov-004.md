---
qid: cpp-opov-004
type: single
kp: [cpp-operator-overload]
difficulty: easy
answer_key: D
---

`operator<<` 用于输出流时，**必须**定义为非成员函数，原因是？

A. 成员函数无法访问私有成员
B. C++ 标准明确禁止将 `<<` 定义为成员函数
C. 非成员函数效率更高
D. `<<` 的左侧是 `ostream` 对象，不是自定义类的对象
