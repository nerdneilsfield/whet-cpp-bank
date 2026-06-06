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

## Explanation

应填 `fetch_add`。`std::atomic` 保证单个对象的原子访问，但是否提供同步还取决于所用内存序。 这个答案对应题干要求的标准名称、成员函数或复杂度写法。常见误区是填写相近但语义不同的接口，或漏掉作用域、大小写、下划线等精确拼写要求。
