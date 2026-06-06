---
qid: cpp-poly-multi-hard-002
type: multi
kp: [cpp-polymorphism]
difficulty: hard
answer_key: [A, C, D]
---
关于多重继承下的 vtable 布局与指针调整，以下说法正确的是哪些？

```cpp
struct A { virtual ~A() = default; virtual int fa(); int a; };
struct B { virtual ~B() = default; virtual int fb(); int b; };
struct C : A, B { int fc(); int c; };
```

A. `C` 对象包含两个基类子对象 `A` 和 `B`，因此包含两组 vptr（指向不同的 vtable）。
B. `C` 中只有一个 vptr，编译器通过名字修饰来区分继承自 `A` 和 `B` 的虚函数。
C. 将 `C*` 向上转型为 `B*` 时，指针需要偏移（adjustment）以指向 `C` 内部的 `B` 子对象——转换是编译器生成的偏移量计算，不是运行时查询。
D. 当 `C::fa()` 从 `B` 的 vtable slot 被调用时（例如通过 `B*` 调用 `fa`），会使用 "thunk" 调整 `this` 指针从 `B` 起点偏移到 `C` 起点。

---

**解析：**

A 正确：多重继承下，每个有虚函数的基类都在派生类中有对应的基类子对象，各自拥有独立的 vptr 指向其 vtable，`C` 对象因此有多组 vptr。
B 错误：每个基类有各自的 vptr，不是"只有一个 vptr"。名字修饰处理的是重载/隐藏/覆盖，不解决 vtable 分发问题。
C 正确：`static_cast<B*>(this)` 在编译期计算已知偏移，不需要查 vtable。在单继承下偏移量为 0，多重继承下非零，这是编译器自动生成的静态调整。
D 正确：当通过 `B*` 调用 `C::fa()`（虚函数覆盖）时，it/vtable entry 指向一个 thunk：thunk 先减 `this` 指针回退到 `C` 起点，再跳转到 `C::fa()`。这是 Itanium C++ ABI 的标准实现。

## Explanation

A、C、D 正确：多重继承中每个含虚函数的基类子对象通常有自己的 vptr，派生对象内部包含多个基类子对象布局。把 `C*` 转成非首基类如 `B*` 需要指针偏移，虚调用覆盖函数时还可能通过 thunk 调整 `this`。常见误区是按单继承模型想象所有对象只有一个 vptr。
