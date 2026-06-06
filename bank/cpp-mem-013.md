---
qid: cpp-mem-013
type: fill
kp: [cpp-memory-mgmt]
difficulty: easy
answer_key: "未定义行为（UB）：double-free / 析构两次"
---

# 阅读代码，指出问题

```cpp
int* p = new int(5);
delete p;
delete p;   // ← 这行有什么问题？
```

第二次 `delete p` 会导致 ______。

<!--
double-free：同一块内存释放两次，属于未定义行为，
通常导致堆损坏或程序崩溃。
-->
