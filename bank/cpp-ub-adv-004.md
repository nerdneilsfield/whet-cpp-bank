---
qid: cpp-ub-adv-004
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: D
---

分析下列代码，编译器在开启优化（`-O2 -fstrict-aliasing`）时最可能输出什么？

```cpp
#include <cstdio>

void modify(float* fp, int* ip) {
    *ip = 0x3F800000;   // IEEE 754 表示 1.0f
    printf("float = %f\n", *fp);
}

int main() {
    float f = 0.0f;
    modify(&f, reinterpret_cast<int*>(&f));
}
```

A. 始终输出 `float = 1.000000`，因为内存被修改了
B. 编译错误，reinterpret_cast 无法转换 float* 到 int*
C. 输出 `float = 0.000000`，因为平台是小端序
D. 输出 `float = 0.000000`，编译器因 strict aliasing 假设 `fp` 与 `ip` 不指向同一对象，缓存了旧值

---

**解析：**

这是 strict aliasing 在函数参数级别的经典场景。

编译器看到 `modify(float*, int*)` 时，依据 strict aliasing 规则：`float*` 和 `int*` 不互相别名。因此它**有权认为 `*ip = …` 不会影响 `*fp`**，并将 `printf` 里的 `*fp` 替换为调用前已知的值（`0.0f`），而不重新从内存加载。

实验：用 GCC 11 `O2` 编译，汇编中 `printf` 的第二参数确实是常量 `0.0`，与 `*ip` 写入无关。

修复方案：
1. 用 `memcpy` 写入（不违反别名规则）
2. 传入 `float*` 而非 `int*` 做修改
3. 用 GCC 扩展 `__attribute__((may_alias))` 标注 `int*`
4. 用 `-fno-strict-aliasing`（关闭优化，非标准方案）

## 解析

正确答案是 D，即 输出 `float = 0.000000`，编译器因 strict aliasing 假设 `fp` 与 `ip` 不指向同一对象，缓存了旧值。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、C 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
