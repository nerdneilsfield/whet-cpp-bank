---
qid: cpp-ub-adv-001
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: C
---

下列代码通过 `int*` 读取 `float` 变量的位模式，行为是？

```cpp
float f = 1.0f;
int* p = reinterpret_cast<int*>(&f);
int val = *p;   // ← 这里
```

A. 完全合法，reinterpret_cast 保证读到正确的位模式
B. 实现定义行为（implementation-defined），各编译器必须记录结果
C. 未定义行为（UB），违反 strict aliasing 规则
D. 只在 `float` 和 `int` 大小不同时才 UB

---

**解析：**

C++ strict aliasing 规则（[basic.lval]）规定：通过类型 T 的左值访问一个实际类型为 U 的对象，只有在 T/U 满足特定兼容关系时才合法（U 与 T 相同、cv 变体、基类、`char`/`unsigned char`/`std::byte` 等）。`float` 和 `int` 没有该兼容关系，因此 `*p` 是 UB。

GCC/Clang 默认开启 `-fstrict-aliasing`，**编译器被允许假设 `p` 与 `&f` 指向不同对象**，可能在寄存器里缓存 `f` 的旧值而不重新加载，导致 `val` 与 `f` 的实际位模式完全无关。

正确做法：
```cpp
int val;
std::memcpy(&val, &f, sizeof(val));   // C++03 起安全
// 或
int val = std::bit_cast<int>(f);      // C++20
```

## Explanation

正确答案是 C，即 未定义行为（UB），违反 strict aliasing 规则。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
