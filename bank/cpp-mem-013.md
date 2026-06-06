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

## Explanation

第二次 `delete p` 会导致未定义行为，典型表现是 double-free、堆损坏或程序崩溃。第一次 `delete` 后对象生命周期已经结束，`p` 变成悬空指针，不能再次释放或解引用。把指针赋为 `nullptr` 可降低重复释放风险，但更推荐用 RAII 类型管理所有权。
