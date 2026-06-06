---
qid: cpp-tmpl-short-003
type: short
kp: [cpp-templates]
difficulty: medium
rubric:
  - 解释 variadic template 接受任意数量、任意类型的模板参数（parameter pack）
  - 说明展开方式（递归终止重载或 C++17 折叠表达式）
  - 给出至少一个典型应用（make_unique/forward/tuple/printf 替代等）
  - 提到 sizeof...(Args) 可获取参数个数
---
请简述 C++ 变参模板（variadic template）的语法机制及其常见用途。

---

**参考答案：**

变参模板用 `template<typename... Args>` 声明参数包，接收数量与类型都可变的模板参数。展开通常有两种方式：传统递归（一个处理首参的重载 + 一个终止重载），或者 C++17 的折叠表达式如 `(std::cout << ... << args)`。`sizeof...(Args)` 可在编译期获取参数个数。典型用途包括 `std::make_unique`、`std::tuple`、完美转发包装器、类型安全的 `printf` 替代等。
