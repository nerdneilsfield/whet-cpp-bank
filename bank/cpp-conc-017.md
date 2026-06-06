---
qid: cpp-conc-017
type: fill
kp: [cpp-concurrency]
difficulty: easy
answer_key: "fetch_add"
---

# 代码阅读：atomic 原子加法

```cpp
std::atomic<int> val{10};
val.____(5);  // 原子地将 val 增加 5，并返回旧值
```

空白处应填写 `std::atomic<int>` 的成员函数名 ____。
