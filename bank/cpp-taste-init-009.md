---
qid: cpp-taste-init-009
type: single
kp: [cpp-cpp14-17, cpp-undefined-behavior]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, string-view, lifetime]
---
一个函数要把用户的 id prefix（某段长字符串的前 4 个字符）提取出来，返回给调用方做字符串比较。四段实现哪个最有品味？

```cpp
// A
std::string_view get_prefix(const std::string& s) {
    return s.substr(0, 4);
}

// B
std::string_view get_prefix(const std::string& s) {
    return {s.data(), 4};
}

// C
std::string get_prefix(const std::string& s) {
    return s.substr(0, 4);
}

// D
std::string_view get_prefix(std::string_view s) {
    return s.substr(0, 4);
}
```

A. A — 最简洁，`s.substr(0,4)` 意图清楚
B. B — 用 data()+长度构造 `string_view`，比 A 少一次分配
C. C — 返回 `std::string`，调用方拿到的就是自有生命周期的字符串
D. D — `string_view` 从 `string_view` 切，链式最自然

---

**解析：**

选 C。这道题考的是 **"`string_view` 是一个借用指针（非拥有视图），用来观察自己不长命的字符串时是安全的；一旦返回给调用方且调用方会用超过原字符串的生命周期，`string_view` 就是悬空指针"**。

逐一品味：

- **A** **未定义行为**。`s.substr(0, 4)` 在 C++11 里返回一个 `std::string`（临时）。`string_view` 从这个临时 string 构造——它保存的指针指向临时 string 的内部 buffer。**函数返回后临时 string 销毁，调用方手里的 `string_view` 的指针悬空**。调用方一读就是 UB。这是新人用 `string_view` 最频繁的踩坑场景——把 `string_view` 当成"省了一次拷贝"然后当作 string 一样返回。
- **B** **同样 UB**。`s.data()` 指向 `std::string s` 的内部 buffer，而 `s` 是函数的 `const&` 参数——当前函数里它是活的，函数返回后参数绑定的那个实参销不销毁？取决于调用方。但到了调用方那里，如果它把 `get_prefix` 返回的 `string_view` 存到某个能活过实参的地方，就是 UB。不解决 A 的根本问题。
- **C** **返回 `std::string`**。`s.substr(0, 4)` 返回 `std::string`，直接 return 它——**NRVO（named return value optimization）**生效，零拷贝。调用方拿到的是 `std::string`，走 RAII 生命周期，想用多久用多久。`string_view` 在返回值签名里面出现，等于在说"我给你的字符串指针指向我自己管理的某个 buffer，它的生命周期*不*长于我的"——如果函数本身就是返回一段不拥有的观察，可以；但这里的 `get_prefix` 语义是"给我一个 prefix 让我自己拿着用"，return `string_view` 是误配契约。
- **D** **同样 UB**。参数已经是 `string_view` 了，从它的子串构造返回的 `string_view`——指针指向参数指向的 buffer。返回值在调用方那里悬不悬空取决于调用方那边传进来的实参生命周期。和 A/B 一样的问题，只是入口从 `const string&` 换成了 `string_view`。D 这种写法在**链式调用**内（调用方在同一个表达式里用完）是安全的，比如 `get_prefix(get_full_name()).size()`——但题目没有说"我只在表达式里用"，正常调用方会 `auto p = get_prefix(name);` 然后久用。

考这条品味的本质：**`string_view` 就是一个带 length 的 `char*`——所有指针生存期规则原封不动适用**。

**核心识别点**：

- 看见函数返回 `string_view` → 立刻检查调用方可不可能在实参生命周期之后用它
- `string_view` 是 **"观察工具"不是"持有工具"**——用作参数、循环内、算法内、用完即弃的临时，是好工具；用作返回值（尤其"给我一个字符串让我存着"的语义）是反模式
- 区分 `string_view` 的**不拥有（non-owning）**和 `std::string` 的**拥有（owning）**：API 契约不同
- 在 C++17 起可以返回 `const std::string&` 的情形除外（比如返回某处永生的字符串字面值或成员）
- 想写出"零拷贝但安全"的 API，用 `std::string` 返回值 + NRVO——编译器会直接消除拷贝（C++17 强制保证）

Bjarne Stroustrup 在 CppCon 2016 上对 `string_view` 有一条著名的警告："`string_view` is a pointer to something that someone else owns." 如果那个"someone else"被销毁了，你拿到的就是一个 `string_view` 的尸体。

**来源：** 手写题。`string_view` 生命周期陷阱见 Marshall Clow "The C++17 Standard Library"、C++ Core Guidelines 的讨论；NRVO / copy elision 见 ISO/IEC 14882:2017 §12.8.2 [class.copy.elision]；Bjarne 在 CppCon 2016 的 keynote 对此有演示。

## Explanation

正确答案是 C。这道题考的是 "`string_view` 是一个借用指针（非拥有视图），用来观察自己不长命的字符串时是安全的；一旦返回给调用方且调用方会用超过原字符串的生命周期，`string_view` 就是悬空指针"。
这道题考的是 "`string_view` 是一个借用指针（非拥有视图），用来观察自己不长命的字符串时是安全的；一旦返回给调用方且调用方会用超过原字符串的生命周期，`string_view` 就是悬空指针"。
常见误区是把新语法等同于直觉糖，忽略 `auto`、列表初始化、lambda 捕获和重载决议的特殊规则。
