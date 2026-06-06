---
qid: cpp-tmpl-short-004
type: short
kp: [cpp-templates]
difficulty: medium
rubric:
  - 区分全特化（full specialization）：为某个具体类型组合提供完全替换的实现
  - 区分偏特化（partial specialization）：保留部分模板参数，仅对一类形态特化
  - 指出函数模板只支持全特化，不支持偏特化（可用重载替代）
  - 类模板既支持全特化也支持偏特化
---
请说明 C++ 模板的全特化（full specialization）与偏特化（partial specialization）的区别，并指出函数模板的特殊限制。

---

**参考答案：**

全特化是为模板的某个具体参数组合提供完全替代的实现，例如 `template<> class Foo<int> { ... };`，编译器在实例化该具体类型时使用特化版本。偏特化仅替换模板参数空间的一个子集，比如 `template<typename T> class Foo<T*> { ... };` 对所有指针类型特化，保留 `T` 为开放参数。需要注意：类模板既支持全特化也支持偏特化，但 **函数模板只支持全特化**，不支持偏特化；想要类似偏特化的效果，通常用函数模板重载或借助类模板偏特化转发来实现。