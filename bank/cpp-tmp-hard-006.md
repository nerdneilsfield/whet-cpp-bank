---
qid: cpp-tmp-hard-006
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: A
---

C++17 fold 表达式中，左折叠与右折叠对于不满足结合律的运算结果不同。以下两个表达式：

```cpp
// 表达式 A（左折叠）
template<typename... Args>
auto left_fold(Args... args) {
    return (... - args);  // ((1 - 2) - 3)
}

// 表达式 B（右折叠）
template<typename... Args>
auto right_fold(Args... args) {
    return (args - ...);  // (1 - (2 - 3))
}

int a = left_fold(1, 2, 3);
int b = right_fold(1, 2, 3);
```

`a` 和 `b` 分别是？

A. `a = -4`，`b = 2`
B. `a = 2`，`b = -4`
C. `a = -4`，`b = -4`
D. `a = 2`，`b = 2`
