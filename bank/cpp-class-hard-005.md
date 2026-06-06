---
qid: cpp-class-hard-005
type: single
kp: [cpp-classes]
difficulty: hard
answer_key: D
---

关于 `[[no_unique_address]]` 属性的行为，以下哪个正确？

```cpp
struct Empty {};
struct A {
    [[no_unique_address]] Empty e1;
    [[no_unique_address]] Empty e2;
    int x;
};
```

A. `e1` 和 `e2` 因共享同一地址导致 `sizeof(A) == sizeof(int)`
B. `[[no_unique_address]]` 只能用于模板参数，不能用于普通数据成员
C. 使用该属性的成员必须满足 `is_empty_v<T>`，否则编译失败
D. `[[no_unique_address]]` 是编译器的许可而非强制，允许多个空子对象重叠同一地址，但同一类型空子对象必须互不重叠；因此 `e1` 与 `e2` 地址不同，`A` 大小通常为 `sizeof(int) + 1`（对齐后 2×sizeof(int)）

## 解析

`[[no_unique_address]]`（C++20）推广了 EBO 思想至成员子对象。它告诉编译器该成员可以与其他成员重叠——但标准要求**同一类型**的子对象地址必须唯一。因此两个 `Empty` 成员 `e1` 和 `e2` 之一起码占用 1 字节的独立地址（除非编译器用了更激进的优化，但标准不强制）。实际布局通常是 `x` 占 0–3 字节，`e1` 在 `x` 末尾填充中重叠，`e2` 在之后占据独立 1 字节，对齐后总大小 2×sizeof(int)。若 `e1` 为 `Empty` 而 `e2` 为另一空类型，则两者可完美重叠，`sizeof(A) == sizeof(int)`。B、C 显然不正。