---
qid: cpp-mem-med-007
type: single
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: B
---

关于 `std::enable_shared_from_this<T>`，以下哪个用法是**正确的**？

A. `auto sp2 = obj.shared_from_this();` 对任何有 `enable_shared_from_this` 基类的对象都安全
B. 必须先有一个 `shared_ptr` 持有该对象，才能调用 `shared_from_this()`，否则抛出 `std::bad_weak_ptr`
C. `shared_from_this()` 内部跨过控制块直接返回一个指向该对象的 `shared_ptr`
D. `enable_shared_from_this` 必须在 `public` 继承才能生效

---

**解析：**

`std::enable_shared_from_this<T>` 的实现原理是：内部持有一个 `weak_ptr<T>`。当 `shared_ptr<T>` 首次构造时，如果检测到 `T` 派生自 `enable_shared_from_this<T>`，就会初始化这个隐藏的 `weak_ptr`。因此**必须先有至少一个 `shared_ptr` 指向该对象**，之后调用 `shared_from_this()` 才能成功升级（从 `weak_ptr` 锁成 `shared_ptr`），否则 `weak_ptr` 未初始化，`lock()` 返回空指针，`shared_from_this` 实现会抛出 `std::bad_weak_ptr`。

常见错误：

```cpp
struct Bad : std::enable_shared_from_this<Bad> {
    auto get() { return shared_from_this(); }   // 没人持有 shared_ptr
};
auto bp = Bad().get();   // 抛出 bad_weak_ptr
```

正确做法：
```cpp
auto sp = std::make_shared<Bad>();
auto sp2 = sp->shared_from_this();   // 安全
```

`shared_from_this()` 的类型是 `shared_ptr<T>`，而非 `T*`（A 错，有前提条件）。C 是错误描述——它返回的是与现有控制块关联的 `shared_ptr`。D 中继承访问权限可以非 `public`（实现只在内部写 `weak_ptr` 成员），但要求 `T` 是 `enable_shared_from_this` 的直接或间接派生类。

## 解析

正确答案是 B，`enable_shared_from_this` 依赖对象已经被某个 `shared_ptr` 的控制块接管，内部弱引用才会被初始化。若在对象尚未由 `shared_ptr` 持有时调用 `shared_from_this()`，会抛出 `std::bad_weak_ptr`。它不是绕过控制块创建新控制块，否则会产生两个控制块和重复释放风险。
