---
qid: cpp-cast-med-001
type: single
kp: [cpp-casting]
difficulty: medium
answer_key: C
---

下列代码中，`dynamic_cast` 在两种用法下的失败行为是？

```cpp
struct Base { virtual ~Base() = default; };
struct Derived : Base {};

Base b;
Base* pb = &b;
Base& rb = b;

Derived* pd = dynamic_cast<Derived*>(pb);   // ①
Derived& rd = dynamic_cast<Derived&>(rb);   // ②
```

A. ① 抛 `std::bad_cast`，② 返回 `nullptr`
B. ① 和 ② 都返回 `nullptr`
C. ① 返回 `nullptr`，② 抛 `std::bad_cast`
D. ① 和 ② 都抛 `std::bad_cast`

---

**解析：**

`dynamic_cast` 失败时的行为依赖目标类型是指针还是引用。对指针类型，失败时返回空指针 `nullptr`，由调用者自行判断；对引用类型，因为不存在“空引用”，只能通过抛出 `std::bad_cast` 异常来报告失败。

这是为引用语义服务的设计：引用一旦存在就必须绑定合法对象，无法用哨兵值表示失败。因此 ① 中 `pd == nullptr`，② 中 `dynamic_cast<Derived&>` 会抛出 `std::bad_cast`（定义于 `<typeinfo>`）。

实践上：检查指针 cast 用 `if (auto* d = dynamic_cast<Derived*>(pb))`，检查引用 cast 用 `try/catch(std::bad_cast&)`。

## 解析

正确答案为 C，因为“① 返回 `nullptr`，② 抛 `std::bad_cast`”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类型转换题要区分编译期转换、运行期检查、cv 限定和底层位模式重解释。
