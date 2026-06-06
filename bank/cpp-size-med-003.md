---
qid: cpp-size-med-003
type: single
kp: [cpp-type-sizes]
difficulty: medium
answer_key: A
---

C++11 的 `alignas` 可以改变类型的对齐要求。以下代码的输出是？

```cpp
#include <iostream>

struct alignas(16) Aligned16 {
    char data[4];
};

struct Default {
    char data[4];
};

struct Mixed {
    char a;
    alignas(32) double b;
    char c;
};

int main() {
    std::cout << sizeof(Aligned16) << " "
              << sizeof(Default) << " "
              << sizeof(Mixed);
}
```

假设 `double` 为 8 字节，默认对齐为 8。

A. `16 4 64`
B. `16 4 40`
C. `32 4 40`
D. `16 4 48`

---

**解析：**

`alignas(N)` 将类型/变量的对齐要求提升到 `N`，同时 `sizeof` 也必须是对齐要求的倍数：

- `Aligned16`：对齐到 16，`char[4]` 占 4 字节，补全到 16 的倍数 → **16**。
- `Default`：默认对齐为 1（char），4 字节无需填充 → **4**。
- `Mixed`：成员 `double b` 声明为 `alignas(32)`，对齐要求提升到 32。布局计算：
  - `char a` 偏移 0
  - `double b` 需偏移为 32 的倍数 → 填充 31 字节到偏移 32（实际上 32 的倍数，从 0→32，填充 31），占 [32, 40)
  - `char c` 偏移 40（对齐 1），占 [40, 41)
  - 结构体整体对齐为 max(1, 32, 1) = 32，`sizeof` 需要是 32 的倍数，41 → 向下个 32 倍数 = **64**。

常见误区：认为 `alignas(32)` 只影响 `b` 的偏移，但不考虑结构体整体大小也必须是对齐的倍数。