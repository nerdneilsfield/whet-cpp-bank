---
qid: cpp-prog-recur-power-001
type: prog
kp: [cpp-functions]
primary_kp: cpp-functions
difficulty: easy
toolchain: [make]
tests_dir: tests/cpp-prog-recur-power-001/
---
实现 `myPow(x, n)`：x^n，O(log |n|)。`n` 可能为负或 `INT_MIN`，注意安全转换。

```cpp
double myPow(double x, int n);
```

## Explanation

使用快速幂，把指数每次折半，奇数指数额外乘一次底数，复杂度 O(log |n|)。负指数返回倒数，`INT_MIN` 不能直接取相反数，应先转换为 `long long`。注意 `n == 0` 返回 1，递归或迭代实现都要处理好符号。
