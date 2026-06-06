---
qid: cpp-taste-class-015
type: single
kp: [cpp-classes, cpp-cpp11, cpp-exceptions]
primary_kp: cpp-classes
difficulty: hard
answer_key: B
tags: [code-taste, best-practice, noexcept]
---
四个版本的 `Vec3` 类，noexcept 标注哪个最品味正确？

```cpp
// A
class Vec3 {
    double x_, y_, z_;
public:
    Vec3() noexcept : x_(0), y_(0), z_(0) {}
    Vec3(double x, double y, double z) noexcept : x_(x), y_(y), z_(z) {}
    Vec3(const Vec3& o) noexcept = default;
    Vec3& operator=(const Vec3& o) noexcept = default;
    double length() const noexcept { return std::sqrt(x_*x_ + y_*y_ + z_*z_); }
    void parse(std::string_view s) noexcept;
};

// B
class Vec3 {
    double x_, y_, z_;
public:
    Vec3() = default;
    Vec3(double x, double y, double z) noexcept : x_(x), y_(y), z_(z) {}
    double length() const noexcept { return std::sqrt(x_*x_ + y_*y_ + z_*z_); }
    void parse(std::string_view s);
};

// C
class Vec3 {
    double x_, y_, z_;
public:
    Vec3() {}
    Vec3(double x, double y, double z) {}
    double length() const { return std::sqrt(x_*x_ + y_*y_ + z_*z_); }
    void parse(std::string_view s);
};

// D
class Vec3 {
    double x_, y_, z_;
public:
    Vec3() throw() : x_(0), y_(0), z_(0) {}
    Vec3(double x, double y, double z) throw() : x_(x), y_(y), z_(z) {}
    double length() const throw() { return std::sqrt(x_*x_ + y_*y_ + z_*z_); }
    void parse(std::string_view s);
};
```

A. A — 所有函数都加 noexcept，包括 parse（即使 parse 内部可能抛）
B. B — 只在不可能抛异常的地方标 noexcept（构造/length），parse 不标
C. C — 全不标，让编译器自由决定
D. D — 用 `throw()` 老式异常规范

---

**解析：**

选 B。这道题考 **noexcept 不是"加上更好"的修饰符，是有语义承诺的**。

逐一品味：

- **A**：**对 parse 标 noexcept 是错误**。如果输入字符串格式非法，parse 怎么报错？三个选择：(1) 不报错，悄悄给出垃圾值——破坏调用方逻辑；(2) 内部 try-catch 把异常转 bool/optional 返回——但接口签名却没体现；(3) 让异常真的抛出——但 noexcept 函数抛异常会直接 `std::terminate()` 程序，无法 catch。**对可能失败的操作标 noexcept 是承诺一个你做不到的事**。
  
  此外，构造函数 `Vec3(double, double, double)` 标 noexcept 是合理的（赋三个 double，绝不抛），但 noexcept 在 `= default` 的拷贝构造里有点冗余——编译器会推断（双精度浮点拷贝是 noexcept）。
- **B**：精准的标注。
  - `Vec3()` 用 `= default`——编译器推断是否 noexcept（这里推断为 noexcept）
  - `Vec3(double, double, double) noexcept`——明确承诺三个 double 赋值不抛
  - `length() const noexcept`——`std::sqrt` 是 noexcept，整体不抛
  - `parse(string_view)`——可能解析失败 → 抛异常，**不**标 noexcept
  
  这种"按真实承诺标注"的态度让 noexcept 成为可信任的接口契约。
- **C**：全不标。每个函数都默认可抛——`length()` 的调用方无法假设"求长度不会抛"，这阻碍了优化。**该标的地方不标是浪费**。
- **D**：`throw()` 是 C++98 的异常规范，C++11 起 deprecated，C++17 移除。语义上和 `noexcept(true)` 不同——`throw()` 在异常发生时调用 `unexpected_handler` 然后 `terminate`，比 noexcept 慢。**完全不要用**。

noexcept 的真正用途：
1. **通信契约**：告诉调用方"这个不会抛"
2. **优化决策**：标准库容器看到 noexcept 的移动构造才使用 move（否则用 copy 以确保 strong guarantee）
3. **接口稳定**：noexcept 是接口的一部分，破坏它是破坏性更改

**核心识别点**：
- noexcept 是承诺，不是装饰——能抛的函数不标
- 移动构造/移动赋值不标 noexcept → 容器退化为 copy，性能灾难
- `= default` 让编译器自动推断 noexcept 性，通常更准
- `throw()` 是 C++98 遗物，废弃

**来源：** 手写题。Scott Meyers "Effective Modern C++" Item 14; C++ Core Guidelines E.12 "Use noexcept when exiting a function because of a throw is impossible or unacceptable"。