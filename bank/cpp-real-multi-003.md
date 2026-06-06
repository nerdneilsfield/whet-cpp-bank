---
qid: cpp-real-multi-003
type: multi
kp: [cpp-cpp11, cpp-cpp14-17, cpp-move-semantics]
primary_kp: cpp-cpp11
difficulty: medium
answer_key: [B, C, D]
tags: [interview-real, multi-vendor]
---
以下特性属于 **C++11** 引入的有哪些（多选）？

A. `if constexpr`（编译期 if）
B. 右值引用与移动语义（`T&&`, `std::move`）
C. `nullptr` 关键字（替代 NULL 宏）
D. `auto` 类型推导
E. structured binding（`auto [a, b] = pair`）
F. fold expressions（`(args + ...)`）

---

**解析：**

正确答案：**B、C、D**。

**C++11 新增特性（部分）：**
- 右值引用、移动语义、`std::move`、`std::forward`
- `nullptr`（取代 NULL = 0 的歧义）
- `auto`、`decltype`
- 范围 for 循环
- lambda 表达式（无 `auto` 参数）
- 智能指针 `unique_ptr` / `shared_ptr` / `weak_ptr`
- `std::thread` / `std::mutex` / `std::atomic`
- 委托构造、统一初始化 `{}`
- `final` / `override`
- variadic templates
- `enum class`
- `noexcept`
- 右值引用资格 `&` / `&&` 成员函数
- `nullptr_t`、`long long`

**C++14：**
- 泛型 lambda（`[](auto x) {...}`）
- `decltype(auto)`
- 变量模板
- 二进制字面量 `0b1010`、数字分隔符 `1'000'000`

**C++17：**
- A. `if constexpr` ✗
- E. structured binding ✗（C++17）
- F. fold expressions ✗（C++17）
- `std::optional` / `std::variant` / `std::any`
- `std::filesystem`
- `[[nodiscard]]`、`[[maybe_unused]]`
- mandatory copy elision
- `std::string_view`

**C++20：**
- concepts、modules、coroutines、ranges
- `std::span`
- `<=>` 三路比较

**来源：** 跨厂 C++ 新特性识别题（参考：cppreference、isocpp.org）