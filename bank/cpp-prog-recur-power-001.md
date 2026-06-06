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