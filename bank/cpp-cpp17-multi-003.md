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

## Explanation

正确答案是 A、B、C。`std::optional<T>` 表示可能有值也可能为空，访问前应检查是否持有值。 A 正确：｀optional<T>｀ 表示「有或没有 T」，｀variant<Ts...>｀ 表示「在若干类型中持有其中一个」。；B 正确：｀optional<T>｀ 可用 ｀*｀ 或 ｀value()｀ 访问；｀variant｀ 通常用 ｀std::get｀ 或 ｀std::visit｀。；C 正确：｀variant｀ 不能默认空，必须至少持有第一个类型的有效值（或 ｀monostate｀）。；D 错误：｀optional<T>｀ 总比 ｀variant<std::monostate, T>｀ 更节省内存。。常见误区是只记住术语名称，而忽略每个选项中的限定条件、生命周期、同步关系或复杂度前提。
