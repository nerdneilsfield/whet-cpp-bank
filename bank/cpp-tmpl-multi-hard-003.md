---
qid: cpp-tmpl-multi-hard-003
type: multi
kp: [cpp-templates]
difficulty: hard
answer_key: [A, B, D]
---
关于 CRTP（Curiously Recurring Template Pattern）的特性，以下说法正确的是哪些？

```cpp
template<typename Derived>
struct Base {
    void interface() { static_cast<Derived*>(this)->impl(); }
    static void s() { Derived::static_impl(); }
};

struct Derived : Base<Derived> { void impl() {} };
```

A. CRTP 实现的是编译期静态多态（static polymorphism），完全不需要 virtual 关键字和 vtable。
B. 若 `Derived` 没有 `impl()`，则 `Base<Derived>::interface()` 的实例化会报错——这是因为 CRTP 的延迟检查（lazy instantiation）特性。
C. CRTP 中的 `static_cast<Derived*>(this)` 存在运行期类型不安全的风险，类似于 dynamic_cast 的运行时开销。
D. CRTP 可配合空基类优化（EBO）使用：若 `Derived` 为空，`Base<Derived>` 经 EBO 后不占用额外空间。

---

**解析：**

A 正确：CRTP 将派生类型作为模板参数传给基类，基类在编译期就知晓派生类类型，通过 `static_cast` 调用派生类方法实现静态分发，完全不需要虚函数。
B 正确：由于模板成员函数是 lazy instantiation（只有被使用时才实例化），若 `Derived` 不含 `impl()`，只要不调用 `interface()` 就不会报错；调用时实例化才报错并定位到错误。
C 错误：`static_cast<Derived*>(this)` 安全的前提是该对象确实通过 `Derived` 构造（而非 `Base<OtherDerived>`），这是 CRTP 的语义约定；但此 cast 是纯编译期零开销操作，不存在 dynamic_cast 的运行时类型检查或 vtable 查询开销。
D 正确：EBO（Empty Base Optimization）允许空基类不占用对象空间；CRTP 中若 `Derived` 为空，`Base<Derived>` 作为空类同样可被 EBO 消除，这是 CRTP 在 small buffer optimization 等场景中常用的技巧。