---
qid: cpp-tmpl-006
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "int"
---

# 类型推导结果

```cpp
template<typename T>
T add(T a, T b) { return a + b; }

auto result = add(3, 5);
```

调用 `add(3, 5)` 时，编译器推导 `T` 为 ___。
