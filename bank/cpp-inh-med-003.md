---
qid: cpp-inh-med-003
type: single
kp: [cpp-inheritance]
difficulty: medium
answer_key: A
---

下列代码输出什么？

```cpp
struct Base   { virtual void who() { std::cout << "Base "; } };
struct Derived : Base { void who() override { std::cout << "Derived "; } };

void byValue(Base b)  { b.who(); }
void byRef  (Base& b) { b.who(); }

Derived d;
byValue(d);
byRef(d);
```

A. `Base Derived `
B. `Derived Derived `
C. `Base Base `
D. `Derived Base `

---

**解析：**

`byValue` 按值接收 `Base`，参数 `b` 是一个全新的 `Base` 子对象，从 `d` 中"切片"（slicing）复制出 `Base` 部分，丢弃 `Derived` 部分。`b` 的动态类型就是 `Base`，虚调用 `who()` 解析为 `Base::who`。

`byRef` 通过 `Base&` 绑定到 `d`，引用不发生对象复制，`b` 的动态类型仍是 `Derived`，虚调用解析为 `Derived::who`。

这就是为什么需要多态行为时**必须**用引用或指针传递基类，按值传递会静默地丢掉派生部分。`-Wsuggest-final-types`/`-Wpessimizing-move` 不会警告这种切片，得靠 code review 或显式禁用基类复制构造来防御。
