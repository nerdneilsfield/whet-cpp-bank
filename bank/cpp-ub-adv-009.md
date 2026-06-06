---
qid: cpp-ub-adv-009
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: C
---

关于内存对齐与未对齐访问，下列说法**正确**的是？

```cpp
#include <cstddef>
#include <iostream>

int main() {
    char buf[8] = {};
    int* p = reinterpret_cast<int*>(buf);     // buf 起始地址，可能对齐
    int* q = reinterpret_cast<int*>(buf + 1); // buf+1，偏移 1 字节

    *p = 42;    // (A)
    *q = 42;    // (B)
}
```

A. (A) 和 (B) 都合法，x86 硬件支持未对齐访问
B. (A) 合法，(B) 只在 32 位平台是 UB，64 位平台安全
C. (A) 可能合法（取决于 `buf` 的对齐），(B) 是 UB（`buf+1` 不满足 `int` 的对齐要求）
D. 两者都是 UB，因为 strict aliasing 规则

---

**解析：**

对齐 UB 与 strict aliasing UB 是两个**独立**问题，此题考查对齐。

**`alignof(int)` 通常为 4**（x86/x86-64/ARM 等主流平台）。

- **(A)**：`buf` 作为 `char[8]` 局部变量，其对齐至少为 `alignof(char) = 1`，**不保证** 4 字节对齐。若 `buf` 的地址恰好 4 字节对齐则 (A) 在对齐层面"运气好"；若不对齐同样是 UB。（注意：实际上编译器常将局部 `char` 数组对齐到更大边界，但标准不保证。）
- **(B)**：即使 `buf` 对齐到 4，`buf+1` 偏移 1 字节后地址模 4 ≠ 0，肯定不满足 `int` 的对齐要求，是 **UB**。

**硬件层面**：x86 的确支持未对齐访问且不崩溃，但：
1. C++ 标准层面仍是 UB（编译器可生成假设对齐的 SIMD 指令等）
2. ARM/RISC-V 等平台直接触发硬件异常

修复：使用 `alignas(int) char buf[8]` 确保 `buf` 对齐到 `int`。
