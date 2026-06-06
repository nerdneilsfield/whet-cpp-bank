---
qid: cpp-cpp17-multi-003
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, B, C]
---
关于 `std::optional` 与 `std::variant` 的区别，**哪些说法是正确的**？（多选）

A. `optional<T>` 表示「有或没有 T」，`variant<Ts...>` 表示「在若干类型中持有其中一个」。
B. `optional<T>` 可用 `*` 或 `value()` 访问；`variant` 通常用 `std::get` 或 `std::visit`。
C. `variant` 不能默认空，必须至少持有第一个类型的有效值（或 `monostate`）。
D. `optional<T>` 总比 `variant<std::monostate, T>` 更节省内存。

---

**解析：**

A 正确：两者用途定义不同。
B 正确：访问方式不同。
C 正确：variant 默认构造为第一个类型，需要表示「空」时常用 `monostate`。
D 错误：内存大小因实现而异，不能一概而论。