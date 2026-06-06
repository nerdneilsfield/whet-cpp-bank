---
qid: cpp-cf-022
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

以下代码中，`for` 循环变量 `i` 在循环结束后是否可在循环外访问？

```cpp
for (int i = 0; i < 5; i++) { }
std::cout << i;  // 此行
```

A. 可以访问，值为 5
B. 可以访问，值为 4
C. 编译错误，`i` 的作用域仅限于 `for` 循环内
D. 运行时崩溃
