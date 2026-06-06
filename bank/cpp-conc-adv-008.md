---
qid: cpp-conc-adv-008
type: single
kp: [cpp-concurrency]
difficulty: easy
answer_key: C
---

关于 `std::promise` 和 `std::future` 的配对使用，描述正确的是？

A. `promise` 和 `future` 是同一个对象的两个引用，必须在同一线程使用
B. `future` 负责设置值，`promise` 负责获取值
C. `promise` 负责设置值（`set_value`），`future` 负责获取值（`get()`），二者可跨线程传递
D. 一个 `promise` 可以与多个 `future` 关联，实现广播
