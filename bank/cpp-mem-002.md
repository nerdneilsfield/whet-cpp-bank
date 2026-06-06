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
