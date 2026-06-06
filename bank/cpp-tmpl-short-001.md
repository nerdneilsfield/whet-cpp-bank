---
qid: cpp-tmpl-short-001
type: short
kp: [cpp-templates]
difficulty: medium
rubric:
  - 指出 SFINAE 全称（Substitution Failure Is Not An Error）
  - 说明在模板实例化时，替换失败不会导致编译终止，只是剔除该重载
  - 给出一个典型用法（如 enable_if 根据类型约束选择特化）
  - 提到 C++20 之后 Concepts 是更优雅的替代方案
---
请解释 C++ 模板元编程中的 SFINAE 原则及其主要用途。

---

**参考答案：**

SFINAE 全称 Substitution Failure Is Not An Error。模板参数替换时，若某个函数模板的重载产生非法类型或表达式（如用 `T::type` 但 `T` 内没有这个类型），该重载被静默移除，但不会造成编译失败。典型用法结合 `std::enable_if`，例如 `enable_if<is_integral_v<T>>` 来为一个类型族启用特化版本。C++20 引入 Concepts 后，多数 SFINAE 技巧被更直观的 `requires` 约束替代。

## Explanation

作答应覆盖：指出 SFINAE 全称（Substitution Failure Is Not An Error）；说明在模板实例化时，替换失败不会导致编译终止，只是剔除该重载；给出一个典型用法（如 enable_if 根据类型约束选择特化）。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 简答题不只要求给结论，还要说明为什么这些规则成立以及错误用法会造成什么后果。常见失分点是只背术语，没有联系代码场景或边界条件。
