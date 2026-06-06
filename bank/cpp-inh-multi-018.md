---
qid: cpp-inh-multi-018
type: multi
kp: [cpp-inheritance]
difficulty: easy
answer_key: [A, C]
---

`std::iostream` 的继承体系是菱形继承的经典例子。下列关于其设计的说法，哪些正确？（多选）

A. `std::istream` 和 `std::ostream` 都虚继承自 `std::ios_base`（经由 `std::basic_ios`）
B. `std::iostream` 使用非虚继承，因此含两份 `ios_base` 子对象
C. 虚继承使 `std::iostream` 对象中只有一份 `basic_ios` 子对象
D. `std::iostream` 不属于菱形继承，`istream` 和 `ostream` 没有共同基类
