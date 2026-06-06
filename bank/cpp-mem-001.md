---
qid: cpp-mem-001
type: single
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: B
---

# 下列哪条语句在堆上分配了一个 `int` 对象？

A. `int x = 42;`
B. `int* p = new int(42);`
C. `int& r = *(new int(42));`（此行本身无问题，但选项 B 更直接）
D. `static int x = 42;`

> 选择最直接体现"堆分配单对象"的语句。

<!--
A — 栈分配
B — 堆分配，正确
C — 也是堆分配，但通过引用绑定，表述绕
D — 静态存储区
-->
