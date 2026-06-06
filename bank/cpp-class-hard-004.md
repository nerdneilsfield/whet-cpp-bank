---
qid: cpp-class-hard-004
type: single
kp: [cpp-classes]
difficulty: hard
answer_key: B
---

`std::is_layout_compatible_v<T, U>` 和 `std::is_trivially_copyable_v<T>` 的含义，以下说法正确的是？

```cpp
struct A { int x; };
struct B { int y; };
// is_layout_compatible_v<A, B> ？
// is_trivially_copyable_v<A>   ？
```

A. 布局兼容意味着可以用 `memcpy` 安全拷贝，因此 `is_layout_compatible` 是 `is_trivially_copyable` 的充分条件
B. 布局兼容只要求两个类型有相同的成员顺序和类型，但不保证可平凡拷贝（trivially copyable 还需无用户定义的拷贝构造/析构等）。`A` 和 `B` 布局兼容且均可平凡拷贝，但用 `memcpy` 从 A 到 B 仍属未定义行为，因为它们是不同类型
C. `is_layout_compatible` 要求两者标准布局且对齐完全一致，`A` 和 `B` 因成员名不同而不布局兼容
D. 若类型合法可平凡拷贝，则可在同一类型间以 `memcpy` 拷贝；布局兼容不同的类型间也可直接 `memcpy`

## Explanation

`std::is_layout_compatible_v<T, U>`（C++17 → C++20 正式）要求 T 和 U 均为标准布局类型，且每个非静态成员的类型、对齐、次序相同——但**成员名不问**。因此 `A` 和 `B` 布局兼容。但布局兼容 ≠ 可平凡拷贝，后者额外要求无虚函数、无用户定义的（非=default）拷贝/移动/析构。即使两者都平凡拷贝且布局兼容，`memcpy` 从 `A` 到 `B` 仍是 UB（strict aliasing 的例外仅允许 `char*`/`unsigned char*` 访问，不适用于 `A*→B*`）。布局兼容仅保证"可以安全地作为 `union` 中的 `active` 成员相互读取"。
