---
qid: cpp-real-en-020
type: multi
kp: [cpp-templates]
primary_kp: cpp-templates
difficulty: medium
answer_key: ["A", "C", "E"]
tags: [interview-real, interviewbit]
---
关于 C++ 模板，以下哪些说法是正确的？（多选）

A. 函数模板（function template）允许对不同类型的参数执行相同逻辑，由编译器生成具体实例
B. 类模板（class template）特化时，部分特化（partial specialization）可以在任意位置声明
C. 模板特化（template specialization）可以为特定类型提供不同的实现
D. 变参模板（variadic template）只能用于函数模板，不能用于类模板
E. 变参模板使用 `typename... Args` 语法，可用 `sizeof...(Args)` 获取参数个数

---

**解析：**

- **函数模板**：如 `template<typename T> T max(T a, T b)`，编译器根据调用参数类型生成具体版本。
- **类模板**：如 `template<typename T> class Vector { }`。
- **模板特化**：分为全特化（full specialization）和部分特化（partial specialization）。全特化后接 `template<>`；部分特化只能在命名空间作用域声明。
- **变参模板（variadic template）**：C++11 引入，`template<typename... Args>`，可用于函数和类模板。`sizeof...(Args)` 获取参数个数。通过递归解包或折叠表达式（C++17 `(op ...)`）处理参数包。

```cpp
template<typename... Args>
void print(Args... args) {
    ((std::cout << args << " "), ...);  // C++17 fold expression
}
```

**来源：** InterviewBit "C++ Interview Questions" — Templates