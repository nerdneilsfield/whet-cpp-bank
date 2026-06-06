---
qid: cpp-ub-013
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 未定义行为
---

# 有符号溢出与编译器优化

```cpp
bool isPositiveAfterAdd(int x) {
    return x + 1 > x;  // 编译器可能优化为 return true
}
```

有符号整数溢出是______，因此编译器可以假设 `x + 1 > x` 永远成立并将函数优化为直接返回 `true`。

（填：未定义行为 / 实现定义行为 / 编译错误 / 合法操作）
