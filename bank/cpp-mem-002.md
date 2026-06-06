---
qid: cpp-mem-002
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: C
---

# 用 `new[]` 分配的数组，必须用 ______ 释放，否则是未定义行为。

A. `delete`
B. `free()`
C. `delete[]`
D. `std::destroy()`

<!--
用 delete（非 delete[]）释放 new[] 数组属于 UB；free() 不匹配 new；
std::destroy() 不是释放函数。答案 C。
-->

## 解析

正确答案是 C，`new[]` 分配的数组必须用匹配的 `delete[]` 释放。用普通 `delete` 释放数组会导致未定义行为，尤其对有析构函数的元素会破坏析构次数和分配器元数据。`free()` 只能匹配 C 的 `malloc` 系列，`std::destroy()` 只析构对象而不释放内存。
