---
qid: cpp-cast-multi-hard-001
type: multi
kp: [cpp-casting]
difficulty: hard
answer_key: [A, B, D]
---
关于 `dynamic_cast` 的特性，以下说法正确的是哪些？

```cpp
struct Base { virtual ~Base() = default; };
struct Derived : Base {};
struct Other  : Base {};

Base* b = new Derived();
Derived* d = dynamic_cast<Derived*>(b);       // (1)
Other* o = dynamic_cast<Other*>(b);           // (2)
Derived& dr = dynamic_cast<Derived&>(*b);      // (3)
```

A. `dynamic_cast` 要求被转换类型必须是**多态类型**（含至少一个 virtual 函数）；否则编译错误。
B. (2) `dynamic_cast<指针>` 失败返回 `nullptr`；(3) `dynamic_cast<引用>` 失败抛出 `std::bad_cast` 异常。
C. `dynamic_cast` 是零开销的：编译器在编译期决议，运行时不查 RTTI。
D. 频繁使用 `dynamic_cast` 通常是设计气味；可考虑虚函数分派、Visitor 模式或 `std::variant` 替代。

---

**解析：**

A 正确：dynamic_cast 依赖 RTTI（运行时类型信息），RTTI 由虚表挂载，因此源类型必须是多态类型；对非多态类型用 dynamic_cast 编译错误。

B 正确：这是 dynamic_cast 的失败处理设计——指针版本可检 nullptr，引用版本不能返回"空引用"故抛异常 `bad_cast`，这区分了两种场景的语义。

C 错误：dynamic_cast 运行时需查 RTTI 信息（如 typeinfo 树），并可能遍历继承链做交叉转换，是 C++ 中开销最大的 cast 之一，比 static_cast/reinterpret_cast 慢得多。性能敏感路径应避免。

D 正确：dynamic_cast 满天飞通常意味着抽象层次划分不合理；替代方案包括：让基类提供 `virtual` 接口（让派生类自身处理）、Visitor 模式（双重分派）、`std::variant + std::visit`（封闭多态）等。