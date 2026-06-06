---
qid: cpp-prog-recur-fibmemo-001
type: prog
kp: [cpp-functions]
primary_kp: cpp-functions
difficulty: medium
toolchain: [make]
tests_dir: tests/cpp-prog-recur-fibmemo-001/
---
带记忆化的递归求 Fibonacci：`fib(0)=0, fib(1)=1, fib(n)=fib(n-1)+fib(n-2)`。`n` 最大可至 60，需用 `long long`。

```cpp
long long fib(int n);
```

## Explanation

用记忆化递归保存已经计算过的 Fibonacci 值，避免朴素递归的指数级重复计算。`fib(0)=0`、`fib(1)=1` 是递归出口，n 到 60 需要 `long long` 保存结果。注意缓存初始化要能区分未计算和结果为 0 的情况。
