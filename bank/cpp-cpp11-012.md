---
qid: cpp-cpp11-012
type: fill
kp: [cpp-cpp11]
difficulty: easy
answer_key: "6"
---

# 代码阅读：constexpr 函数求值

阅读以下代码，`result` 的值是多少？

```cpp
constexpr int square(int n) { return n * n; }

int main() {
    constexpr int result = square(2) + square(1) + square(1);
    // result = ?
}
```

`result` 的值为：___
