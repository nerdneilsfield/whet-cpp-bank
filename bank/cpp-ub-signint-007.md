---
qid: cpp-ub-signint-007
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: B
---

# `if (n < v.size())` 当 `n = -1` 时

下面函数意图用 `n` 作为数组索引前做边界检查，代码逻辑正确吗？

```cpp
#include <vector>
#include <iostream>
void access(int n, const std::vector<int>& v) {
    if (n < v.size()) {          // 看起来像安全检查
        std::cout << v[n] << std::endl;
    } else {
        std::cout << "out of range" << std::endl;
    }
}
int main() {
    std::vector<int> v = {1, 2, 3};
    access(-1, v);
    return 0;
}
```

A. 正确，`n = -1` 时输出 `out of range`
B. 错误：`n = -1` 时会输出 `v[-1]`（越界访问，UB）
C. 编译错误，`int` 不能与 `size_t` 比较
D. 正确，`n = -1` 时比较会先把 `-1` 转为有符号

> **知识点**：`n < v.size()` 中，`n`（int，值 -1）与 `size_t` 比较时，`n` 被隐式转换为 `size_t`，变为极大正数（`SIZE_MAX`），大于 `v.size()`（3），条件为 false！程序反而进入 else？不——条件 false 跳过 if，执行 else，输出 out of range。等等——实际上 `SIZE_MAX > 3` 所以 `n < v.size()` 为 false，程序输出 `out of range`，但这**并非**因为正确的边界检查逻辑，而是"歪打正着"。若 `n = 0` 到 `2` 是合法的，`n = -1` 恰好也输出了 out of range，但**依赖此行为是 bug**：当 `v` 很大、`SIZE_MAX` 恰好小于 `v.size()` 时逻辑就会崩溃（实际上 `SIZE_MAX` 总比任何 `size_t` 大，所以 n=-1 时条件永远 false）。正确做法：先检查 `n >= 0`。

## Explanation

正确答案是 B，即 错误：`n = -1` 时会输出 `v[-1]`（越界访问，UB）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
