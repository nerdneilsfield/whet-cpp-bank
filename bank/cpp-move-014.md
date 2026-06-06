---
qid: cpp-move-014
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

# 代码阅读：函数返回临时对象

以下函数返回时，编译器最可能采用什么优化？

```cpp
std::vector<int> make_vec() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    return v;
}

auto result = make_vec();
```

A. 拷贝构造，将 v 完整拷贝到 result
B. NRVO/RVO（返回值优化），直接在 result 的内存中构造 v，零拷贝
C. 移动构造，v 被移动到 result
D. 编译错误，不能返回局部变量
