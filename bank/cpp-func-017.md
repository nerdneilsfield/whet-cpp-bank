---
qid: cpp-func-017
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

以下代码每次调用 `counter()` 输出什么序列（连续调用三次）？

```cpp
void counter() {
    static int cnt = 0;
    cnt++;
    std::cout << cnt << " ";
}
```

A. `0 0 0`
B. `1 2 3`
C. `1 1 1`
D. 编译错误
