---
qid: cpp-tmpl-010
type: fill
kp: [cpp-templates]
difficulty: easy
answer_key: "编译错误（T 推导冲突：int vs double）"
---

# 类型推导冲突

```cpp
template<typename T>
T max(T a, T b) { return a > b ? a : b; }

auto result = max(1, 2.0);
```

上述代码的编译结果是：___。
