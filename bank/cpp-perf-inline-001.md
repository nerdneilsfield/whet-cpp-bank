---
qid: cpp-perf-inline-001
type: single
kp: [cpp-functions, cpp-build-tools]
primary_kp: cpp-functions
difficulty: hard
answer_key: B
tags: [performance, code-taste]
---

要实现一个"取两个 int 较大者"的工具函数 `imax`，调用方在另一个 .cpp 里写**热循环**调用它。下面四种实现/编译策略功能等价，哪个最值得采用？

```cpp
// A
// util.cpp:
int imax(int a, int b) { return a > b ? a : b; }
// util.h:
int imax(int a, int b);

// B
// util.h:
inline int imax(int a, int b) { return a > b ? a : b; }
// caller.cpp: #include "util.h"

// C
// util.cpp:
int imax(int a, int b) { return a > b ? a : b; }
// util.h:
int imax(int a, int b);
// 编译: clang++ -O3 -flto util.cpp caller.cpp

// D
// util.h:
__attribute__((always_inline)) inline int imax(int a, int b) { return a > b ? a : b; }
```

A. A — 在 .cpp 实现 + 头文件声明，标准编译
B. B — 把实现写在头里加 inline，每个 TU 自己看见
C. C — 在 .cpp 实现 + LTO 让链接器跨 TU 内联
D. D — always_inline 强制编译器内联

---

**解析：**

选 B。这道题考的是"何时需要让函数定义在每个 TU 都可见，编译器才能内联"。

逐一品味：

- **A**：函数实现在 util.cpp，调用方的 caller.cpp 只看到声明。编译 caller.cpp 时，编译器**不知道 imax 内部是什么**——只能生成一条 `call imax` 指令（一次间接跳转 ~5–10 cycles + 函数体 ~2 cycles + 返回 ~2 cycles）。imax 本身就一条 cmov 指令，**调用开销比函数体大 5 倍**。在 1e9 次循环调用里就是几秒 vs 毫秒的差距。无 LTO 时这是 C++ 默认行为。
- **B**：函数定义在头里加 `inline`——`inline` 关键字主要语义是"允许多个 TU 有相同定义"（去 ODR），但**实际副作用**是每个 TU 都看见函数体、编译器可以自由内联。调用方 caller.cpp 编译时直接把 `a > b ? a : b` 内联成 `cmov` 指令——**完全消解函数调用**。这是 C++ 一行小工具函数的标准做法。**最简单、跨编译器、无需特殊编译选项**。
- **C**：LTO（链接时优化）让链接器看到所有 TU 的 IR，可以做跨 TU 内联，**效果等同 B**。但 ① 要求构建系统启用 `-flto`，CI 配置错就退化成 A；② LTO 链接时间显著增加（大项目 ~2–10× 链接时间）；③ 调试构建一般不开 LTO，意味着 debug 性能比 release 差几个数量级。**能解决问题但代价大**，且把"语言层面应该做到的事"推到了 build flag。
- **D**：`always_inline` 强制内联（即使 `-O0` 也尝试）。但前提是**编译器能看见函数体**——如果 D 的函数体在头里（题目其实就在头里）那效果和 B 一样；如果在 .cpp 里，attribute 也救不了。本题 D 的实现就在头里，所以**效果等同 B**，但 `always_inline` 是 GCC/Clang 扩展，MSVC 是 `__forceinline`，不跨编译器；且 attribute 取消了编译器的判断权，对大函数强制内联可能伤 icache。B 更标准。

B 优于 D 的原因不是性能（一样），而是**用标准语言机制而非编译器扩展**，跨编译器、零代码味道。

**核心识别点：**
- 看见"小工具函数实现写在 .cpp 里"被热循环调用 → 警觉编译器无法跨 TU 内联，函数调用开销远大于函数体
- 看见用 LTO 拯救"接口/实现分离" → 警觉这是构建复杂度换语言简洁，且依赖 build flag
- 看见 `always_inline`/`__forceinline` → 警觉是不是把内联决定从编译器手里夺过来
- 一个 1-line 函数：调用开销 ~10 cycles，函数体本身 ~1 cycle——内联与否差 10 倍
- 模板自动满足这个特性（必须在头里），是它在性能代码里盛行的原因之一

**来源：** Scott Meyers, "Effective C++" 3rd ed., Item 30 "Understand the ins and outs of inlining"；C++ 标准 [dcl.fct.spec]；Matt Godbolt, "What Has My Compiler Done for Me Lately?", CppCon 2017.
