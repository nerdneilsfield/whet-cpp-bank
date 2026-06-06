---
qid: cpp-bp-multi-med-001
type: multi
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: [A, B, C, D]
---
区分以下场景的标准定义级别，**哪些说法是正确的**？（多选）

A. 有符号整型溢出（`INT_MAX + 1`）是**未定义行为**（UB），编译器可基于"无溢出"假设进行优化
B. 无符号整型溢出（`UINT_MAX + 1u`）是**良定义**的，按模 2^N 回绕
C. `char` 是 `signed` 还是 `unsigned`，是**实现定义**的（implementation-defined），不同编译器/平台可能不同
D. 函数实参的求值顺序在 C++17 之前是**未指明的**（unspecified），不是 UB，但可能产生不同结果

---

**解析：**

A 正确：有符号溢出 UB，是编译器常做激进优化（如 `i+1 > i` 恒为真）的基础。要严格定义需 `-fwrapv` 或使用 `__builtin_add_overflow`。
B 正确：标准明确规定无符号算术按 2^N 取模，没有溢出 UB。
C 正确：纯 `char` 的符号性由实现决定（ARM 上常为 unsigned，x86 多为 signed）。需要明确符号应用 `signed char` 或 `unsigned char`。
D 正确：函数实参之间的求值顺序在 C++17 之前是 unspecified（每次执行是某种合法顺序，但具体顺序不保证），这不是 UB；不同编译器/优化级别下结果可能不同。C++17 引入了更多顺序点，但参数之间仍未指明。

四个选项均正确——UB、implementation-defined、unspecified 的区别是 C++ 工程师必须掌握的基础概念。

## Explanation

A、B、C、D 都正确：未定义行为、实现定义行为和未指明行为是三种不同标准概念。有符号溢出是 UB，无符号回绕是良定义，`char` 符号性由实现说明，函数实参求值顺序属于未指明而非 UB。常见误区是把所有“结果不确定”都叫 UB，导致错误判断编译器能否优化。
