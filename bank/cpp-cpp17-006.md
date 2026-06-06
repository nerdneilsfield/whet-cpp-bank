---
qid: cpp-cpp17-006
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: C
---

# 认知：C++14 泛型 lambda

C++14 引入了泛型 lambda，下列哪种写法使用了该特性？

A. `auto f = [](int x) { return x * 2; };`
B. `auto f = []<typename T>(T x) { return x; };`
C. `auto f = [](auto x) { return x * 2; };`
D. `template<> auto f = [](int x) { return x; };`
