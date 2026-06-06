---
qid: cpp-move-011
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

# 代码阅读：拷贝还是移动？

以下代码调用的是拷贝构造函数还是移动构造函数？

```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = v1;
```

A. 移动构造函数，因为 v1 在之后不再使用
B. 拷贝构造函数，因为 v1 是具名 lvalue
C. 移动构造函数，因为赋值号右边是 v1
D. 编译器自动选择，结果不确定
