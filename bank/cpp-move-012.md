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

## Explanation

正确答案是 A，`std::move(v1)` 将具名左值 `v1` 转换为 xvalue，使 `vector` 的移动构造函数成为更优匹配。移动会把资源从 `v1` 转给 `v2`，但 `v1` 本身仍有效。`std::move` 不是拷贝，也不是只能用于临时对象。
