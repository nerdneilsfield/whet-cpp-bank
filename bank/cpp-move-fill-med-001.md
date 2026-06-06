---
qid: cpp-move-fill-med-001
type: fill
kp: [cpp-move-semantics]
difficulty: medium
answer_key: "std::move"
---
将左值转换为右值引用调用 ___。

---

**解析：**

`std::move` 是 `<utility>` 中的函数模板，本质上执行无条件的 `static_cast<T&&>` 转换。它不移动任何东西——只是一个"转型器"，通知编译器接下来可以对该对象进行移动操作。移动语义的有效性取决于移动构造函数/赋值运算符的实现是否正确。