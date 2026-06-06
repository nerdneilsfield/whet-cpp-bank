---
qid: cpp-cpp17-multi-001
type: multi
kp: [cpp-cpp14-17]
difficulty: medium
answer_key: [A, B, D]
---
关于 C++17 结构化绑定（structured bindings）的来源，**哪些是合法的绑定对象**？（多选）

A. 数组：`auto [a, b, c] = std::array<int,3>{...};`
B. `std::pair` 与 `std::tuple`。
C. 任意有 `operator[]` 的容器。
D. 用户自定义类型，只要其 public 数据成员可被聚合解包，或特化了 `tuple_size`/`tuple_element`。

---

**解析：**

A 正确：原生数组与 `std::array` 都可被结构化绑定。
B 正确：通过 `get<I>`、`tuple_size`、`tuple_element` 支持。
C 错误：`operator[]` 不能用于结构化绑定，必须满足三种支持形式之一。
D 正确：通过聚合形式或显式定制 `tuple_size`/`tuple_element` 都能支持。