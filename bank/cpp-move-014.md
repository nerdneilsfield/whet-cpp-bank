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

## 解析

正确答案是 B，返回局部对象初始化同类型结果时，编译器通常可做 NRVO/RVO，直接在调用方结果对象中构造，避免拷贝和移动。即使无法消除，C++11 后也通常会优先移动而非拷贝。误区是认为返回局部变量一定悬空；按值返回会返回对象本身，不是引用。
