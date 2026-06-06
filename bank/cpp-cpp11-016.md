---
qid: cpp-cpp11-016
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: D
---

# 代码阅读：decltype 推导类型

阅读以下代码，`y` 的类型是什么？

```cpp
int x = 10;
int& ref = x;
decltype(ref) y = x;
```

A. `int`
B. `int*`
C. `const int&`
D. `int&`
