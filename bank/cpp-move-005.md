---
qid: cpp-move-005
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: D
---

# 移动后对象的状态

对一个 `std::vector` 执行移动操作后，被移动的对象处于什么状态？

A. 已销毁，不可再访问
B. 保留原始数据的副本
C. 一定为空（`size() == 0`）
D. 有效但未指定（valid but unspecified），可以安全销毁或重新赋值
