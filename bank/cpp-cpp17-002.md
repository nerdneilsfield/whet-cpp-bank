---
qid: cpp-cpp17-002
type: single
kp: [cpp-cpp14-17]
difficulty: easy
answer_key: C
---

# 认知：if constexpr 的用途

关于 `if constexpr`，下列说法正确的是？

A. 运行时根据条件选择分支，和普通 `if` 完全相同
B. 只能用于模板特化，不能用于普通函数
C. 在编译期对条件求值，未选中的分支不会被实例化
D. 等价于 `#ifdef` 预处理指令

## Explanation

正确答案是 C。`constexpr` 表示可在编译期求值，适用于需要常量表达式的场合。选项 C 的表述“在编译期对条件求值，未选中的分支不会被实例化”正好符合该规则。A、B、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
