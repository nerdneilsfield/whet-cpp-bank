---
qid: cpp-algo-008
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: C
---

`std::remove` 和 `std::remove_if` 的返回值是什么？

A. 被删除元素的数量
B. 指向第一个被"删除"元素的迭代器
C. 指向新逻辑末尾（past-the-new-end）的迭代器
D. `void`，无返回值

## Explanation

正确答案是 C。`std::remove` / `std::remove_if` 不会真正缩小容器，而是把保留元素移动到前部，并返回“新逻辑末尾”迭代器。真正删除尾部无效区间需要再调用容器的 `erase`，即 erase-remove idiom。
