---
qid: cpp-cast-hard-003
type: single
kp: [cpp-casting]
difficulty: hard
answer_key: C
---

C++20 `std::bit_cast<Dst>(src)` 与 `memcpy` / `union` 相比的优势是？

```cpp
float f = 3.14f;
// 方案1
std::uint32_t i1;
std::memcpy(&i1, &f, sizeof(f));
// 方案2
union { float f; std::uint32_t i; } u{f};
auto i2 = u.i;
// 方案3
auto i3 = std::bit_cast<std::uint32_t>(f);
```

下列说法最准确的是？

A. 三者完全等价
B. `bit_cast` 性能最差因为是模板
C. `bit_cast` 是 `constexpr`（在两种类型都是可平凡复制且无成员可见性问题时），可用于编译期；`memcpy` 直到 C++26 才被部分允许在常量表达式中使用，`union` 的类型双关在标准上是 UB（C 中合法但 C++ 中读非 active 成员未定义），仅 `bit_cast` 既零开销又类型安全且 `constexpr` 友好
D. `union` 读非 active 成员在 C++ 中是合法的"类型双关"

## 解析

`std::bit_cast`（C++20）专为类型双关（type punning）设计：要求两个类型大小一致且都是可平凡复制（trivially copyable）。它在语义上等价于 `memcpy` 但是 **`constexpr`**（编译期可用），且无需中间临时变量。`memcpy` 一直是合法做法但非 `constexpr`（直至 C++26 提案中部分放宽）。`union` 在 C 中合法但 **C++ 不支持通过非 active 成员读取**——这条规则在 C++ 中明确是 UB（即使大多数编译器作为扩展接受）。因此 `bit_cast` 在新代码中是首选：可作为变量初始化器在 `constexpr` 上下文使用，编译器通常优化为零代价。