---
qid: cpp-tmpl-007
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "double"
---

# 显式模板参数

```cpp
template<typename T>
T add(T a, T b) { return a + b; }

auto result = add<double>(3, 5);
```

`result` 的类型是 ___。
