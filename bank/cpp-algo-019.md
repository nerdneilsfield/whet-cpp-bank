---
qid: cpp-algo-019
type: multi
kp: [cpp-algorithms]
difficulty: easy
answer_key: [B, D]
---

以下哪些说法关于 `std::remove` / `std::remove_if` 是**正确**的？（多选）

A. 调用 `std::remove` 后，容器的 `size()` 立即减小
B. `std::remove` 并不真正删除元素，只是将不需要的元素移到范围末尾
C. `std::remove` 返回被移除元素的个数
D. 要真正删除元素，需要配合容器的 `erase` 成员函数（erase-remove idiom）
