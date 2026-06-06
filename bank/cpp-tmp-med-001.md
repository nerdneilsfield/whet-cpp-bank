---
qid: cpp-tmp-med-001
type: single
kp: [cpp-templates]
difficulty: medium
answer_key: B
---

关于函数模板与类模板的特化，下列说法**正确**的是？

A. 函数模板和类模板都支持偏特化（partial specialization）
B. 函数模板只支持全特化，不支持偏特化；类模板既支持全特化也支持偏特化
C. 函数模板支持偏特化，但类模板不支持偏特化
D. 函数模板和类模板都不支持偏特化，只能通过重载模拟

---

**解析：**

C++ 标准规定：

- **类模板**（class/struct template）：同时支持**全特化**（`template<> struct Foo<int>`）和**偏特化**（`template<typename T> struct Foo<T*>`）。
- **函数模板**：仅支持**全特化**（`template<> void f<int>(int)`）。不支持偏特化，但可以通过**函数重载**实现类似的分派效果。

这是 C++ 设计中一个常见的"非对称性"，初学者容易混淆。
