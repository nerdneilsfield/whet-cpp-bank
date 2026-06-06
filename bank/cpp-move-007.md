---
qid: cpp-move-007
type: single
kp: [cpp-move-semantics]
difficulty: easy
answer_key: B
---

# 右值引用延长临时对象生命周期

以下代码中，临时 `std::string` 的生命周期如何？

```cpp
std::string&& ref = std::string("hello");
// 此处继续使用 ref
```

A. 临时对象在该语句结束后立即销毁，ref 成为悬空引用
B. 临时对象的生命周期被延长到 ref 的作用域结束
C. 编译器报错，右值引用不能绑定临时对象
D. 临时对象被拷贝一份，ref 绑定到副本
