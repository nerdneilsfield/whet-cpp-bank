---
qid: cpp-ub-hard-003
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: B
---

有符号整数溢出在 C++ 中是如何影响编译器优化的？

```cpp
int square(int n) {
    if (n < 0) n = -n;       // 当 n = INT_MIN 时，-n 是未定义行为
    int r = n * n;            // 若 n > 46340 则 int 溢出
    return r;
}
```

A. 有符号整数溢出会回绕，结果等于 `(a*b) mod 2^32`（2 的补码算术），没问题
B. 有符号整数溢出是未定义行为，编译器可假设"不会发生溢出"（actually UB-demon key optimizations），因此 `n * n` 的结果可被直接视为正确，甚至利用此假设消除边界检查、推断循环范围。上述 `square` 若传 `INT_MIN` 或 `46341` 等值，完全不可预测，可能返回任意值或删除安全检查
C. 仅乘法溢出有 UB，取负 `-n` 在 2 的补码里总是安全的
D. C++20 已将整数溢出定义为回环绕行，不再有 UB

## Explanation

C++ 标准明确规定有符号整数的溢出是 UB（无符号整数按模运算安全）。这为编译器打开了大量优化门扉：因为"假设不会发生溢出"，编译器可以推断某条件必然成立（如 `a > b` 必假若乘法可能溢出时）、简化算术表达式、消除分支等。取负（`-n`）在 `n == INT_MIN` 时也是 UB，因为 `-INT_MIN` 在 2 的补码 32 位中表示 +2147483648 超出 `int` 范围。C++20 未改变这条规则——仍为 UB。A 错在认为"会回绕"——标准没保证，尽管大多数 x86 硬件回绕。C 错同。D 不存在。
