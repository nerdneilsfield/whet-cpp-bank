---
qid: cpp-smf-med-004
type: single
kp: [cpp-special-members]
difficulty: medium
answer_key: B
---

下列代码用 C++11 起的语法编译，构造 `Foo f;` 后 `f.x` 与 `f.y` 的值分别是？

```cpp
struct Foo {
    int x = 1;          // 默认成员初始化器 (DMI)
    int y = 2;
    Foo() : y(20) {}    // 构造函数初始化器列表只显式提到 y
};
```

A. `x = 0`,  `y = 0`
B. `x = 1`,  `y = 20`
C. `x = 1`,  `y = 2`
D. `x = 0`,  `y = 20`

---

**解析：**

[class.base.init] 规定的初始化优先级是：**构造函数初始化器列表**（mem-initializer-list）覆盖**默认成员初始化器**（DMI，class member initializer）。两者表达同一个语义：每个成员只被初始化一次，谁出现在 ctor-init-list 谁说了算；没出现的成员才退回使用 DMI。

因此：
- `x` 没在 `Foo()` 的初始化列表中出现 → 使用 DMI `= 1`，`x == 1`。
- `y` 在初始化列表中被赋为 `20` → DMI 的 `= 2` 被**完全忽略**（不是先 2 再 20，编译器只生成一次初始化）。

注意 DMI 与 ctor-init-list 并不存在“先执行 DMI 再执行 ctor-init-list”的运行时叠加；它们在同一抽象语义槽位上互斥。这也意味着 `int y = expensive();` 与 `Foo() : y(20)` 共存时，`expensive()` 不会被调用。

## 解析

正确答案是 B，构造函数初始化列表中显式初始化的成员会使用该初始化器，未出现的成员才使用默认成员初始化器。`x` 未在 `Foo()` 初始化列表出现，所以取 DMI 的 1；`y` 被初始化列表设为 20，类内的 `=2` 不再生效。它不是先按 DMI 初始化再赋值，而是每个成员只初始化一次。
