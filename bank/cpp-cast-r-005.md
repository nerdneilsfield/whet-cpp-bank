---
qid: cpp-cast-r-005
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

### 题目

下面代码通过 `reinterpret_cast` 读取 `float` 的位模式，输出是什么？

```cpp
#include <iostream>
#include <cstdint>

int main() {
    float f = 1.0f;
    uint32_t bits = *reinterpret_cast<uint32_t*>(&f);
    // IEEE 754: 1.0f = 0 01111111 00000000000000000000000 = 0x3F800000
    if (bits == 0x3F800000u) {
        std::cout << "correct bit pattern" << std::endl;
    } else {
        std::cout << "unexpected: " << std::hex << bits << std::endl;
    }
    return 0;
}
```

A. 编译错误：不能对 `float*` 使用 `reinterpret_cast`
B. 输出 `correct bit pattern`（在 IEEE 754 平台上）
C. 输出 `unexpected: ...`（reinterpret_cast 不保留位模式）
D. 运行时崩溃

## Explanation

B


`reinterpret_cast<uint32_t*>(&f)` 将 `float*` 重新解释为 `uint32_t*`，再解引用即可读取 `float` 的原始 32 位存储。在符合 IEEE 754 标准的平台（绝大多数现代硬件）上，`1.0f` 的位模式正好是 `0x3F800000`，因此条件成立，输出 `correct bit pattern`。注意：严格来说这里存在"type-punning"，标准允许的做法是使用 `memcpy` 或 C++20 的 `std::bit_cast`，但此处 `reinterpret_cast` 在主流编译器上实际可用。
