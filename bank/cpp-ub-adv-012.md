---
qid: cpp-ub-adv-012
type: single
kp: [cpp-undefined-behavior]
difficulty: hard
answer_key: C
---

下列代码中，编译器（`-O2`）可能基于 UB 假设消除空指针检查，最终输出是什么？

```cpp
#include <cstdio>

int* global_ptr = nullptr;

void process(int* p) {
    *p = 42;              // (1) 解引用 p
    if (p == nullptr) {   // (2) 空指针检查
        global_ptr = p;
        printf("null branch\n");
    }
}

int main() {
    int x = 0;
    process(&x);
}
```

A. 输出 `null branch`，因为 `global_ptr` 是 nullptr，满足条件
B. 什么都不输出，且 (2) 处检查按正常流程执行
C. 什么都不输出，且编译器可能完全删除 `if (p == nullptr)` 分支
D. 编译器报警告但不影响行为

---

**解析：**

这是**UB 驱动的编译器优化**（"UB implies dead code elimination"）的经典案例。

推理链：
1. `(1)` 处对 `p` 解引用（`*p = 42`）
2. 若 `p == nullptr`，则 `(1)` 是 UB（空指针解引用）
3. 编译器**假设程序不含 UB**，因此推断：**执行到 `(1)` 时，`p` 必然非 nullptr**
4. 既然 `p != nullptr` 在 `(1)` 之后恒成立，`(2)` 的 `p == nullptr` 分支**永远不会被执行**
5. 编译器合法地将整个 `if` 块删除

实验验证（GCC 11 -O2）：生成的汇编中 `if (p == nullptr)` 分支完全消失，`global_ptr` 永远不被赋值，`printf` 永远不被调用。

**实际危害**：开发者常写"防御性检查"，先解引用再检查 nullptr，以为检查能捕获问题——殊不知前面的解引用已经让编译器消除了该检查。

**修复**：将 nullptr 检查移到解引用**之前**。

## 解析

正确答案是 C，即 什么都不输出，且编译器可能完全删除 `if (p == nullptr)` 分支。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
