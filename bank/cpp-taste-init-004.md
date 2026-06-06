---
qid: cpp-taste-init-004
type: single
kp: [cpp-cpp14-17, cpp-classes]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: D
tags: [code-taste, best-practice, initialization, static-members]
---
要在头文件里定义一个类的"常量配置表"——一个静态 `std::map<std::string, int>` 成员。下面四个写法哪个最有品味（项目编译器支持 C++17）？

```cpp
// A
// config.hpp
class Config {
public:
    static const std::map<std::string, int> table;
};

// config.cpp
const std::map<std::string, int> Config::table = {{"a", 1}, {"b", 2}};

// B
// config.hpp
class Config {
public:
    static const std::map<std::string, int> table = {{"a", 1}, {"b", 2}};
};

// C
// config.hpp
class Config {
public:
    static constexpr std::map<std::string, int> table{{"a", 1}, {"b", 2}};
};

// D
// config.hpp
class Config {
public:
    inline static const std::map<std::string, int> table{{"a", 1}, {"b", 2}};
};
```

A. A — 类内声明 + 类外定义，C++98 起就正确的写法
B. B — 类内直接初始化，省掉 .cpp 文件
C. C — `constexpr` 表达"编译期常量"，最现代
D. D — `inline static` 把声明和定义合为一处，头文件单点维护

---

**解析：**

选 D。这道题考的是 **"C++17 的 `inline` 变量解决了头文件里静态成员的老麻烦"**。

逐一品味：

- **A**：C++98/11/14 唯一能编过的写法——类内只能写**声明**，定义必须放到一个翻译单元的 `.cpp` 里，否则多个 `.cpp` `#include` 这个头文件就会产生多个定义，链接器报 ODR 违规。代码本身没错，但**强迫维护两个文件**：改一条配置要同时改 `.hpp` 和 `.cpp`，**或者**改一个忘改另一个 → 链接错误。一种"被语言逼出来的丑陋"。
- **B**：**编译不过**。类内初始化器对**非 `const`/`constexpr` 的静态数据成员**是非法的；即使是 `const`，类内初始化也**只对 integral / enumeration 类型生效**（§9.4.2 [class.static.data]）。`std::map` 不是 integral 类型，写在类内只能用 `inline`（C++17）或类外定义。这条规则是 C++ 长期的不对称之一。
- **C**：**编译不过**。`constexpr` 要求类型是 **literal type**——构造函数必须 constexpr、析构函数必须 trivial 或 constexpr。`std::map` 的构造函数**不是 constexpr**（它做堆分配），析构也不是 trivial。所以 `constexpr std::map<...>` 在任何 C++ 标准下都是非法的。"`constexpr` 比 `const` 更强"是对的，但**不等于"什么都能 constexpr"**。看到 `constexpr` 套在 `std::map` / `std::vector` / `std::string` 上要立刻警觉——直到 C++20 这些还都不能 constexpr，C++20 才让 `std::vector` / `std::string` 部分 constexpr（仅在 constant evaluation 中），`std::map` 至今（C++23）仍不行。
- **D**：C++17 引入的 `inline` 变量是为这场景量身定做的。`inline static` 让**类内的定义**自动避开 ODR——多个翻译单元 include 同一份头，链接器把所有 `inline` 定义合并成一份。结果：**头文件单点定义，无 .cpp 文件**，改一行就完。这是 C++17 之后头文件库（header-only）的标准做法。

**核心识别点**：

- 看见 **类内有非整型 `static` 成员的初始化器** → 想到 C++17 之前是非法的、C++17 之后必须加 `inline`
- 看见 **`constexpr` 套在非 literal type**（map / vector 在 C++17/20 之前、string 在 C++20 之前、map 至今）→ 知道编不过
- 看见 **头 + .cpp 拆开维护一个常量表** → 想想能不能用 `inline static` 收回头里
- `inline` 变量（C++17）和 `inline` 函数（C++98）共享同一条 ODR 豁免规则——理解 `inline` 的本质是"允许多份定义"，不是"建议内联"
- `static constexpr` 的 integral 成员从 C++17 起**隐式 inline**（§9.2.3.2/3），不用再写 `inline`；但**非整型 constexpr 成员**仍需要 `inline` 或类外定义

C++17 之前的"静态成员必须有 .cpp 定义"这条规则坑了无数模板库作者——你不能在纯头文件里安放任何非整型常量。`inline` 变量把这道围墙拆掉，是 C++17 一个不显眼但极重要的进步。

**来源：** 手写题。`inline` 变量见 ISO/IEC 14882:2017 §10.1.6 [dcl.inline]/6；类内静态成员初始化规则见 §9.4.2 [class.static.data]；`constexpr` 对 literal type 的要求见 §7.1.5 [dcl.constexpr]。
