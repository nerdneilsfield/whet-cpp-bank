---
qid: cpp-move-short-003
type: short
kp: [cpp-move-semantics]
difficulty: medium
rubric:
  - 解释完美转发要保持参数的左值/右值类别和 const 属性
  - 指出实现依赖通用引用 T&& 与 std::forward<T>
  - 解释引用折叠规则（T& && -> T&, T&& && -> T&&）
  - 给出典型应用（make_unique、emplace_back 等包装器）
---
请解释 C++ 中的完美转发（perfect forwarding）以及它依赖的关键机制。

---

**参考答案：**

完美转发指函数模板将其接收的参数以"原汁原味"的左值/右值类别、const/volatile 限定转发给另一个函数，避免无意义的拷贝或类别退化。它依赖两个机制：一是函数模板形参 `T&&` 作为通用引用（forwarding reference），结合引用折叠规则（`T& &&` 折叠成 `T&`，`T&& &&` 折叠成 `T&&`），使形参既能匹配左值也能匹配右值；二是 `std::forward<T>(arg)` 根据 `T` 是否为引用类型，把 `arg` 还原回原本的值类别。典型应用包括 `std::make_unique`、容器的 `emplace_back`、各种通用包装器。

## Explanation

完美转发是指模板包装函数把参数以原来的左值/右值类别转交给目标函数。它依赖 `T&&` 转发引用的特殊推导、引用折叠规则，以及 `std::forward<T>` 按 `T` 恢复值类别。常见误区是直接传 `arg` 或统一用 `std::move(arg)`；前者会把右值变左值，后者会误移动左值。
