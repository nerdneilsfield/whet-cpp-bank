---
qid: cpp-taste-init-006
type: single
kp: [cpp-cpp14-17, cpp-stl-basics]
primary_kp: cpp-cpp14-17
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, optional, null-semantics]
---
要写一个函数 `find_user`：按 id 查用户，**找不到时返回"空"**。User 是一个小的值类型（48 字节、可拷贝）。四个返回类型设计哪个最有品味？

```cpp
// A
User find_user(int id) {  // 找不到返回 User{-1, "", ""}
    if (auto* p = lookup(id)) return *p;
    return User{-1, "", ""};
}

// B
std::optional<User> find_user(int id) {
    if (auto* p = lookup(id)) return *p;
    return std::nullopt;
}

// C
std::unique_ptr<User> find_user(int id) {
    if (auto* p = lookup(id)) return std::make_unique<User>(*p);
    return nullptr;
}

// D
bool find_user(int id, User& out) {
    if (auto* p = lookup(id)) { out = *p; return true; }
    return false;
}
```

A. A — 用 id == -1 当 sentinel，调用方少一层解包
B. B — `std::optional<User>` 把"可空"写在类型里，意图直达
C. C — `unique_ptr` 既能表达 null 又能省 User 的存储（不存在就不分配）
D. D — out-parameter + bool 返回值是 C 风格 API 中最稳的模式

---

**解析：**

选 B。这道题考 **"用类型表达可空，而不是用约定/魔法值/堆指针/输出参数"**。

逐一品味：

- **A** **sentinel 值反模式**。`id == -1` / `""` 是**约定**——文档里写、新人看不到、半年后维护者翻文档才知道。一旦哪天有合法的 id = -1（系统升级、新业务），所有调用方默默走错分支。类型系统毫无帮助。Tony Hoare 把 null sentinel 称为他的 ["billion-dollar mistake"](https://en.wikipedia.org/wiki/Tony_Hoare#Apologies_and_retractions) 不是夸张。
- **B** `std::optional<User>`：**"可空"是类型的一部分**。返回值在编译器层面就强制调用方"先 check has_value / 用 `*` 解包"，忘检查 → 类型不匹配编译错；用 `.value_or(default)` 一行优雅 fallback。**无堆分配**——optional 在栈上 inline 存储 User + 一个 bool（实际可能因对齐占 sizeof(User) + 8）。意图、安全、性能三赢。
- **C** `std::unique_ptr<User>`：**也表达了 null**，但用了**堆分配**——每次"找到"都要 `make_unique<User>(*p)` 一次 `new`、调用方读一次解一层指针。本来 User 才 48 字节，栈传递快得很，硬要塞进堆是技术债。`unique_ptr` 表达的是 **"唯一所有权 + 可空 + 大对象/多态/PIMPL"** 这套组合，单纯为了"可空"用它是误配工具。
- **D** **out-parameter** 是 C 没有 `optional` 时不得已的妥协。三个问题：
  1. `User& out` 要求调用方**先构造一个 User**（默认构造可能开销不小、或根本不允许默认构造），结果可能根本不用——浪费。
  2. **两个返回通道**（bool + out）让调用方更容易出错：`if (find_user(id, u)) use(u);` 写反成 `find_user(id, u); use(u);` 就读未初始化。
  3. **不能链式**：`find_user(...).transform(...)` 在 B 里很自然，D 里不可能。
  C++ 还有 reference 输出参数语义不清（看不出来是输出还是输入引用）的老问题——所以 Google C++ style guide 长期建议输出参数用指针 `User* out`，更糟。

**核心识别点**：

- 看见 sentinel 值（-1、""、INT_MAX、空对象）当 null → 类型系统没在帮忙，警觉
- 表达"可空"的优先级：**`optional<T>` > `T*`（不拥有的可空指针） > `unique_ptr<T>`（拥有、堆、可多态）> sentinel / out-param**
- `unique_ptr<T>` 是**所有权 + 堆 + 多态**三合一工具，不要为了"可空"单点功能用它
- C++17 之后**没有理由**再为新代码设计 out-parameter 的查找/解析 API
- `optional<T>::transform`、`.and_then`、`.value_or`（C++23）让链式调用代码远比 if-else 干净

C 时代用 `int errno + T* out` 是因为 C 没有 sum type；C++17 给了 optional / variant / expected（C++23）三件套，**应该用就用**。`optional<T>` 用了之后的代码读起来像是"我返回的就是'可能有可能没有的 User'"——这种类型即文档的体验是现代 C++ 的核心 selling point。

**来源：** 手写题。`std::optional` 见 ISO/IEC 14882:2017 §23.6 [optional]；理念见 P0091r3 提案及 Andrzej Krzemienski 的 "Efficient optional values" 系列文章；Tony Hoare 的 null mistake 见 his "Null References: The Billion Dollar Mistake" talk (QCon London 2009)。
