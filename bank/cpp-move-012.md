---
qid: cpp-move-012
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: A
---

# 代码阅读：std::move 触发移动

以下代码调用的是什么构造函数？

```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = std::move(v1);
```

A. 移动构造函数，`std::move(v1)` 将 v1 转为右值引用
B. 拷贝构造函数，`std::move` 实际上是拷贝
C. 默认构造函数
D. 编译错误，不能对具名变量使用 `std::move`
