---
qid: cpp-cpp1417-short-001
type: short
kp: [cpp-cpp14-17]
difficulty: medium
rubric:
  - 解释结构化绑定将聚合体/tuple/pair 的成员一次性解包到多个具名变量
  - 给出语法示例 `auto [k, v] = *map.begin();`
  - 指出可用 const auto& / auto& 控制是否拷贝或绑定引用
  - 提到与基于范围 for 联合使用遍历 map
---
请解释 C++17 中的结构化绑定（structured bindings），并给出一个典型用例。

---

**参考答案：**

结构化绑定允许一次性把一个聚合体、`std::tuple`、`std::pair` 或公开数据成员的类的各个字段绑定到多个具名变量，避免反复 `first/second` 之类的访问。语法形如 `auto [a, b, c] = expr;`，可以加 `const auto&` 或 `auto&` 来控制是按值拷贝还是按引用绑定。最常见的用例是遍历 map：

```cpp
for (const auto& [key, value] : m) {
    std::cout << key << " : " << value << '\n';
}
```

代码可读性比 `it->first / it->second` 显著提升。

## Explanation

`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。 本题短答应围绕核心概念展开：结构化绑定允许一次性把一个聚合体、｀std::tuple｀、｀std::pair｀ 或公开数据成员的类的各个字段绑定到多个具名变量，避免反复 ｀first/second｀ 之类的访问。语法形如 ｀auto [a, b, c] = expr;｀，可以加 ｀const auto&｀ 或 ｀auto&｀ 来控制是按值拷贝还是按引用绑定。最常见的用例是遍历 map： ｀｀｀cpp for (const auto& [key, value] : m) { std::cout << key << " : " << value  评分重点包括：解释结构化绑定将聚合体/tuple/pair 的成员一次性解包到多个具名变量；给出语法示例 `auto [k, v] = *map.begin();`；指出可用 const auto& / auto& 控制是否拷贝或绑定引用。常见误区是只给出结论、不说明机制，或忽略异常路径、同步边界、生命周期等限制条件。
