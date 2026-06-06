---
qid: cpp-tmpl-016
type: single
kp: [cpp-templates]
difficulty: easy
answer_key: B
---

# 模板实例化时机

```cpp
// a.h
template<typename T>
T identity(T x) { return x; }

// a.cpp
#include "a.h"

// b.cpp
// #include "a.h" 未包含

int main() {
    int r = identity(42); // 此处调用
}
```

若 `b.cpp` 未包含 `a.h`，`main` 中调用 `identity(42)` 的结果是？

A. 正常编译，模板已在 `a.cpp` 中实例化
B. 编译错误，`identity` 未声明
C. 链接错误，找不到 `identity<int>` 的定义
D. 运行时错误

## Explanation

正确答案是 B，即 编译错误，`identity` 未声明。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
