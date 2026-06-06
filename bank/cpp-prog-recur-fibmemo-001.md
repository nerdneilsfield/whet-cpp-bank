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