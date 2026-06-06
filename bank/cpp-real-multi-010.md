---
qid: cpp-real-multi-010
type: multi
kp: [cpp-polymorphism, cpp-inheritance]
primary_kp: cpp-polymorphism
difficulty: medium
answer_key: [A, B, C]
tags: [interview-real, multi-vendor]
---
```cpp
class Base {
public:
    virtual void f();
    virtual void g() final;
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void f() override;
    // void g() override;   // 错误：g 在 Base 中是 final
};

class Final : public Derived final {  // Final 类不能再被继承
public:
    void f() override;
};
```
关于 `override`、`final`、`virtual` 关键字的组合规则，以下说法**正确**的是（多选）：

A. `override` 用于派生类，表示重写基类虚函数，编译器会检查签名是否匹配
B. `final` 既可用于**类**（禁止继承）也可用于**虚函数**（禁止重写）
C. 派生类重写虚函数时，`override` 关键字是可选的（不写也是重写），但**强烈推荐**写以利用编译期检查
D. `virtual` 关键字必须在派生类的重写函数上重复写
E. `final` 和 `override` 是 C++98 引入的

---

**解析：**

正确答案：**A、B、C**。

**A 正确：** `override` 是 C++11 引入的**修饰符**（不是关键字，是"identifier with special meaning"）。它的核心价值是**编译期检查**：
- 如果"派生类函数"实际上没有重写任何基类虚函数（比如参数列表打错、const 漏写、基类没有该虚函数）→ 编译错误
- 如果基类虚函数后来被改了签名或删除，所有 override 标记的派生函数都会编译报错

**B 正确：** final 两种用法：
- **类后**：`class C final { ... };` 禁止继承 C
- **虚函数后**：`virtual void f() final;` 该函数不能在派生类重写

final 类的对象不能切片访问，编译器可做**去虚拟化（devirtualization）优化**，把虚调用替换为直接调用。

**C 正确：** override 不写不影响语义，但写了能防止：
- 拼写错误（`virtual void f()` → 派生写成 `void F()`）
- 签名差异（`virtual void f(int)` → 派生写成 `void f(double)`）
- 漏写 const（`virtual void f() const` → 派生写成 `void f()`）

**D 错误：** virtual 在派生类**可写可不写**。一旦基类标 virtual，整个继承链所有同签名函数都是 virtual。常见风格是只在基类写 virtual，派生类只写 override。

**E 错误：** override 和 final 是 **C++11** 引入的，不是 C++98。它们也不是关键字（avoid breaking existing code that uses `override` as variable name）。

**最佳实践组合：**
```cpp
// 基类
class Base {
public:
    virtual void method() = 0;  // virtual + 纯虚
    virtual ~Base() = default;
};

// 派生类（叶子）
class Concrete final : public Base {  // 标 final 类
public:
    void method() override;   // 标 override
};
```

**来源：** 跨厂 C++11 关键字考查（参考：cppreference、Effective Modern C++ Item 12）

## Explanation

正确答案：A、B、C。
A 正确： override 是 C++11 引入的修饰符（不是关键字，是"identifier with special meaning"）；C 正确： override 不写不影响语义，但写了能防止： 拼写错误（virtual void f() → 派生写成 void F()） 签名差异（virtual void f(int) → 派生写成 void f(double)） 漏写 const（virtual void f() const → 派生写成 void f()） ；D 错误： virtual 在派生类可写可不写。
它的核心价值是编译期检查： 如果"派生类函数"实际上没有重写任何基类虚函数（比如参数列表打错、const 漏写、基类没有该虚函数）→ 编译错误 如果基类虚函数后来被改了签名或删除，所有 override 标记的派生函数都会编译报错 ；B 正确： final 两种用法： 类后：class C final { ... }; 禁止继承 C 虚函数后：virtual void f() final; 该函数不能在派生类重写 final 类的对象不能切片访问，编译器可做去虚拟化（devirtualization）优化，把虚调用替换为直接调用。
