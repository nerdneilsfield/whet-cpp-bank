---
qid: cpp-x-enum-cast-001
type: single
kp: [cpp-enum, cpp-casting]
primary_kp: cpp-enum
difficulty: medium
answer_key: B
---

下列代码使用 `enum class`，哪些行编译失败？

```cpp
#include <cstdint>

enum class Color : std::uint8_t { Red = 1, Green = 2, Blue = 4 };

int main() {
    Color c = Color::Red;

    int x = c;                            // (1)
    int y = static_cast<int>(c);          // (2)
    Color d = 1;                          // (3)
    Color e = static_cast<Color>(2);      // (4)
    bool isRed = (c == Color::Red);       // (5)
    bool any   = (c != 0);                // (6)
}
```

A. 只有 (3)
B. (1)(3)(6) 编译失败；其余合法
C. (1)(2)(3)(6) 编译失败
D. (3)(6) 编译失败；其余合法

---

**解析：**

`enum class`（**scoped enumeration**，C++11 引入）与传统 `enum`（unscoped enum）的核心差异：

1. **不会隐式转换为整数类型**——必须显式 `static_cast`。
2. **不会隐式从整数构造**——同样需要 `static_cast`。
3. **枚举值有作用域限定**：必须用 `Color::Red`，不能直接 `Red`。
4. **可以指定底层类型**（如 `: std::uint8_t`），保证 ABI 稳定。
5. **同类型枚举间** 的 `==`、`!=`、`<`、`>` 比较是合法的，因为不需要类型转换。

逐项分析：

- **(1) `int x = c;`** — `Color` 不会隐式转换为 `int`，**编译失败**。
- **(2) `int y = static_cast<int>(c);`** — 显式转换，合法，`y = 1`。
- **(3) `Color d = 1;`** — `int` 不能隐式转换为 `Color`，**编译失败**。需要 `static_cast<Color>(1)`。
- **(4) `Color e = static_cast<Color>(2);`** — 合法，即使 2 不是已定义的枚举值，C++ 也允许（值在底层类型范围内即可），`e == Color::Green`。
- **(5) `c == Color::Red`** — 两边都是 `Color`，合法。
- **(6) `c != 0`** — 左边 `Color`，右边 `int`，没有隐式转换，**编译失败**。必须写成 `c != Color{0}` 或 `static_cast<int>(c) != 0`。

C++23 引入 `std::to_underlying(c)`，提供更明确的语义：

```cpp
#include <utility>
int y = std::to_underlying(c);   // C++23
```

`enum class` 的设计理念是 **类型安全**——通过禁止隐式转换，避免 `enum` 时代「不同枚举可以混用、可与整数自由换算」导致的 bug。代价是显式 cast 较多，但换来编译期类型检查的可靠性。