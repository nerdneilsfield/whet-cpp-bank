---
qid: cpp-func-011
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: A
---

下列递归函数计算阶乘，`factorial(3)` 的返回值是多少？

```cpp
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

A. `6`
B. `3`
C. `9`
D. `1`
