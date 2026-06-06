---
qid: cpp-tmpl-014
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: C
---

# 显式模板参数解决冲突

```cpp
template<typename T>
T max(T a, T b) { return a > b ? a : b; }
```

要用 `1` 和 `2.0` 调用 `max` 且让 `T=double`，正确写法是？

A. `max(1, 2.0)`
B. `max<>(1, 2.0)`
C. `max<double>(1, 2.0)`
D. `max(double(1), 2.0)` 不行，只能用显式模板参数
