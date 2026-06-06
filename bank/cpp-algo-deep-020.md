---
qid: cpp-algo-deep-020
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
---

下列比较器违反严格弱序（strict weak ordering），用于 `std::sort` 是 UB。哪项是**问题所在**？

```cpp
auto cmp = [](int a, int b){ return a <= b; };
std::sort(v.begin(), v.end(), cmp);
```

A. 比较器不能用 lambda
B. 必须传 `std::less<int>{}` 才合法
C. `<=` 违反**反自反性**：`cmp(x,x)` 必须为 `false`，但 `<=` 返回 `true`
D. `<=` 对浮点数不安全

## 解析

正确答案是 C：sort 的比较器必须满足严格弱序，其中 cmp(x,x) 必须为 false。a <= b 在 a 等于 b 时返回 true，违反反自反性，可能导致 sort 行为未定义。正确比较器应使用 <，并特别注意 NaN 等会破坏有序关系的值。
