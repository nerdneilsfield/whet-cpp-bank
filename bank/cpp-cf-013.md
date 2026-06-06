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
