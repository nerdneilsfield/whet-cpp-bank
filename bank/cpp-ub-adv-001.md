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
