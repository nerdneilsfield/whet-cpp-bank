---
qid: cpp-arrptr-short-001
type: short
kp: [cpp-arrays-pointers]
difficulty: medium
rubric:
  - 解释数组在大多数上下文（传参、表达式）会"退化"为指向首元素的指针
  - 指出退化后 sizeof 不再返回数组总大小、丢失长度信息
  - 给出例外：sizeof / & / decltype / typeid 不会退化
  - 提到通过引用或 std::span / std::array 保留长度信息
---
请解释 C 风格数组在 C++ 中的"退化"（decay）行为，以及它带来的问题。

---

## 解析

在大多数表达式中，C 风格数组会"退化"为指向其首元素的指针，例如把 `int a[10]` 传给 `void f(int*)` 时，函数内只剩一个指针，丢失了长度 10 的信息，`sizeof(parm)` 只返回指针大小。退化使得使用裸数组容易越界、难以泛型化。例外情况：在 `sizeof(a)`、`&a`、`decltype(a)`、`typeid(a)` 中以及作为引用 `int (&)[10]` 绑定时不会退化，可以保留类型信息。推荐做法是用 `std::array<T,N>` 或 `std::span<T>`，既保留长度又有 STL 风格接口。