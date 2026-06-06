---
qid: cpp-taste-init-002
type: single
kp: [cpp-cpp11, cpp-stl-basics]
primary_kp: cpp-cpp11
difficulty: hard
answer_key: C
tags: [code-taste, best-practice, initialization]
---
一个类持有一个 `std::string name_` 和一个 `const int id_`，构造函数从参数初始化它们。四个写法哪个最有品味？

```cpp
// A
class User {
    std::string name_;
    const int id_;
public:
    User(std::string name, int id) {
        name_ = name;
        id_ = id;
    }
};

// B
class User {
    std::string name_;
    const int id_;
public:
    User(std::string name, int id) : name_(), id_(0) {
        name_ = std::move(name);
        const_cast<int&>(id_) = id;
    }
};

// C
class User {
    std::string name_;
    const int id_;
public:
    User(std::string name, int id) : name_(std::move(name)), id_(id) {}
};

// D
class User {
    std::string name_{};
    const int id_{0};
public:
    User(std::string name, int id) : name_{std::move(name)}, id_{id} {}
};
```

A. A — 在函数体里赋值最直观
B. B — 先零初始化再赋值，保证两阶段的明确性
C. C — 成员初始化列表 + `std::move`，干净
D. D — 在声明处给默认成员初始化器 + 列表里再覆盖，最安全

---

**解析：**

选 C。这道题考 **"成员初始化列表 vs 函数体赋值"** 的基本品味，但用 `const` 成员把刀架在脖子上。

- **A** **编译不过**。`const int id_` 不能在函数体里被赋值——`id_` 已经被默认初始化（`int` 在类内是 indeterminate value），然后 `id_ = id` 违反 const。`name_ = name` 这一行也是一次默认构造 + 一次拷贝赋值，把"构造时给值"这个简单事拆成两步，本来一次拷贝构造就能搞定。A 的根问题是**把"初始化"和"赋值"混为一谈**。
- **B** 用 `const_cast` 绕开 const 是 **未定义行为**：对原本声明为 const 的对象做 `const_cast` 后写入，违反 §7.1.6.1 [dcl.type.cv]。运行能跑只是侥幸——优化器有权假设 const 对象的值不变。这种"我知道但我硬来"的写法在 review 里应该被一票否决。
- **C** 是教科书答案：
  1. **`const` 成员只能在初始化列表里给值**——这是语言强制的硬约束。
  2. **`name_(std::move(name))`** ——`name` 是按值传进来的（已经是一份独立拷贝/move 后的对象），在列表里 `std::move` 进成员，是 Scott Meyers Item 41 的"sink parameter"模式：lvalue 调用方付 1 次拷贝、rvalue 调用方零拷贝，成员永远只是 move 构造。
  3. **没有函数体**——根本不需要。一行说完。
- **D** 在声明处加默认初始化器 `name_{}` / `id_{0}`，看似双保险，实际是**双初始化**：成员先按声明处的默认值初始化，紧接着被列表里的值覆盖。对 `std::string` 是一次额外的空 string 构造（虽然便宜），对 `const int` 是一次先写 0 再写 id 的冗余。更严重的是**信号噪音**——读者会问"为什么要先给默认值？是不是某个构造分支不会覆盖？" 实际上所有构造分支都覆盖，那默认值就是多余的装饰。默认成员初始化器的合理用法是**那些有的构造函数不覆盖的成员**，不是"所有构造都会赋的成员"。

**核心识别点**：

- 看见 `const`/引用成员在函数体里被赋值 → 立刻知道编译不过或者作者用了非法绕过
- 看见 `const_cast` 写 const 对象 → UB，直接一票否决
- 区分**初始化（一步到位）vs 赋值（先默认构造再覆盖）**：能用初始化列表绝不在函数体里赋值
- 按值接 + `std::move` 进成员 = sink parameter idiom，应该认得出来
- 默认成员初始化器（`name_{}`）只在"有的构造路径不覆盖它"时才加，否则是噪音

成员初始化列表不是"风格选择"，是 **C++ 对象模型的强制语法**：const 成员、引用成员、没有默认构造函数的成员，**必须**在列表里初始化。把列表当作可选优化是新人最常见的误读。

**来源：** 手写题。语言规则见 ISO/IEC 14882 §12.6.2 [class.base.init]；sink parameter 见 Scott Meyers *Effective Modern C++* Item 41；`const_cast` 写 const 对象的 UB 见 [dcl.type.cv]/4。

## Explanation

正确答案是 C。这道题考 "成员初始化列表 vs 函数体赋值" 的基本品味，但用 `const` 成员把刀架在脖子上。
这道题考 "成员初始化列表 vs 函数体赋值" 的基本品味，但用 `const` 成员把刀架在脖子上。
`const int id_` 不能在函数体里被赋值——`id_` 已经被默认初始化（`int` 在类内是 indeterminate value），然后 `id_ = id` 违反 const。
