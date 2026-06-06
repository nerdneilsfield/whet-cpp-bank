---
qid: cpp-ub-adv-010
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: D
---

下列代码中，`*p = 42` 的行为是？

```cpp
#include <cstdint>

int main() {
    char buf[5] = {};
    int* p = reinterpret_cast<int*>(buf + 1);  // buf+1 地址
    *p = 42;
}
```

假设 `int` 的对齐要求为 4 字节（`alignof(int) == 4`）。

A. 合法；`char` 数组的元素地址连续，任何偏移访问 `int` 都没问题
B. 实现定义行为：x86 平台保证结果正确
C. 只要 `buf` 本身 4 字节对齐，`buf+1` 也合法
D. UB：`buf+1` 的地址不满足 `int` 的对齐要求（4 字节对齐），同时违反 strict aliasing

---

**解析：**

此处有**两层 UB 叠加**：

1. **对齐违规**：`buf` 是 `char[5]`，对齐保证仅为 1 字节。`buf+1` 地址为 `buf地址 + 1`，即使 `buf` 恰好 4 字节对齐（地址 % 4 == 0），`buf+1` 的地址 % 4 == 1，不满足 `alignof(int) == 4`，解引用是 UB。

2. **Strict aliasing 违规**：`char buf[5]` 不存在 `int` 对象，通过 `int*` 访问 `char` 数组内容（`char` 不是 `int` 的兼容类型反方向不成立——`char*` 可别名 `int*`，但 `int*` 不能别名 `char` 数组）。

**平台行为**：x86 硬件允许未对齐访问（带性能惩罚），程序通常不崩溃，但编译器在 `-O2` 下可能生成 SSE/AVX 指令（假设对齐），导致信号错误或错误值。

**修复**：
```cpp
alignas(int) char buf[sizeof(int) + 1];
int* p = reinterpret_cast<int*>(buf);  // buf 本身已对齐，但仍有 strict aliasing 问题
// 真正安全：直接声明 int 变量
```

## Explanation

正确答案是 D，即 UB：`buf+1` 的地址不满足 `int` 的对齐要求（4 字节对齐），同时违反 strict aliasing。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
