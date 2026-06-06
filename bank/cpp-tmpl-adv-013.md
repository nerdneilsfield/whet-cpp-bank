---
qid: cpp-tmpl-adv-013
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

关于 `std::enable_if<condition, T>::type`，当 `condition` 为 `false` 时会发生什么？

A. 编译报错，提示条件不满足
B. 该重载仍然保留，但调用时抛出运行时异常
C. 该 `::type` 不存在，导致模板替换失败，该重载从候选集中被静默移除（SFINAE）
D. 返回 `void` 类型
