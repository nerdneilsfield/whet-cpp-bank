---
qid: cpp-mod-multi-med-003
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, C, D]
---
关于 `std::optional<T>` 与 `std::variant<Ts...>` 的对比，**哪些说法是正确的**？（多选）

A. `std::optional<T>` 等价于 `std::variant<std::monostate, T>` 的语义：要么有值，要么无值
B. `std::variant<int, int>` 是非法的，不允许有重复类型
C. 访问 `std::variant` 当前未持有的类型会抛 `std::bad_variant_access`；访问空 `optional` 的 `value()` 会抛 `std::bad_optional_access`
D. 两者都默认不进行动态内存分配，存储是内嵌的（in-place）

---

**解析：**

A 正确：`optional<T>` 的二态语义等价于 `variant<monostate, T>`，但 `optional` 在 API 设计上更轻量、专门化。
B 错误：`std::variant<int, int>` 是**合法的**，只是不能通过类型访问（`get<int>` 会编译失败），必须用下标 `get<0>`/`get<1>`。
C 正确：两者都用对应的异常类型表达"访问错误状态"。
D 正确：两者的存储都使用对齐的内嵌缓冲区，不需要堆分配（区别于 `unique_ptr`、`any` 的小对象优化策略）。
