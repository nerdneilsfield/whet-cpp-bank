---
qid: cpp-cpp11-002
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: B
---

# 认知：统一初始化防止窄化转换

以下哪条语句在 C++11 中会触发**编译错误**（窄化转换被禁止）？

A. `int a = 3.0;`
B. `int b{3.14};`
C. `double c{3.14};`
D. `int d(3);`
