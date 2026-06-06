---
qid: cpp-taste-param-002
type: single
kp: [cpp-move-semantics, cpp-functions]
primary_kp: cpp-move-semantics
difficulty: hard
answer_key: B
---

下面四段代码都实现"把一个 string 存进成员里"的 setter。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
class User {
    std::string name_;
public:
    void set_name(const std::string& n) { name_ = n; }
};
```

```cpp
// B
class User {
    std::string name_;
public:
    void set_name(std::string n) { name_ = std::move(n); }
};
```

```cpp
// C
class User {
    std::string name_;
public:
    void set_name(const std::string& n) { name_ = std::move(n); }
};
```

```cpp
// D
class User {
    std::string name_;
public:
    void set_name(std::string&& n) { name_ = std::move(n); }
    void set_name(const std::string& n) { name_ = n; }
};
```

A. A 段：`const&` 是经典写法，永远只传引用，绝对安全。
B. B 段：按值接 + `std::move`，左值时一次拷贝、右值时一次移动，代码只有一行。
C. C 段：先 `const&` 接、再 `move`，"两全其美"。
D. D 段：左值版 + 右值版重载，每种情况单独优化，最专业。

## 解析

正确答案是 **B**。

- **A 段（差）**：右值传进来（如 `set_name(std::string("Alice"))`）也只能拷贝，丢掉了移动机会；对于 sink 这种"一定要存下来"的参数，是典型的次优写法。
- **B 段（好）**：sink 参数的标准范式。左值实参 → 形参拷贝构造 → 成员移动赋值，总成本 = 一次拷贝；右值实参 → 形参移动构造 → 成员移动赋值，总成本 = 两次移动（≈ 一次拷贝的零头）。代码量最少，覆盖所有情形。
- **C 段（错）**：`const std::string&` 上的 `std::move` 退化为 `const string&&`，**无法绑定到移动构造函数的非 const `string&&`**，最终静默地落回拷贝。`move` 写了个寂寞，还误导读者以为做了优化——比 A 更糟。
- **D 段（差）**：两个重载只是手写了 B 段的展开形式，多写了一倍代码、API 噪声更多；遇到三个 string 入参就要写 8 个重载。仅当 profiler 证明 sink 的拷贝是热点、且想为右值省下"形参移动构造"那一步时，才考虑。

**核心识别点：**
- "sink 参数"（一定要存进对象的入参）写法：**按值接 + `std::move` 进成员**。
- `const T&` 上调 `std::move` 没用——会退化成 `const T&&`，绑不到非 const 的移动构造。
- 用值传 + move 的代价 = 拷贝；不会比 `const&` 更慢，但能吃到右值的移动红利。
- 重载左右值是"已被语言机制取代"的旧写法，仅在拷贝是性能热点时考虑。

**来源：** Effective Modern C++ Item 41；Herb Sutter "Back to the Basics" CppCon 2014；Abseil tips of the week #117。
