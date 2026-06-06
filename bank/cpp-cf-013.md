---
qid: cpp-cf-013
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: B
---

以下代码中 `break` 的作用是什么？

```cpp
for (int i = 0; i < 10; i++) {
    if (i == 5) break;
    std::cout << i << " ";
}
```

A. 跳过 `i == 5` 这一次迭代，继续循环
B. 立即终止整个 `for` 循环
C. 程序直接退出 `main`
D. 只跳过 `std::cout` 语句

## Explanation

正确答案为 B，因为“立即终止整个 `for` 循环”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
