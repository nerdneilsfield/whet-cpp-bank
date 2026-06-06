---
qid: cpp-tmp-hard-007
type: single
kp: [cpp-templates]
difficulty: hard
answer_key: B
---

以下代码使用 C++17 fold 表达式打印所有参数：

```cpp
#include <iostream>

template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args);
}

int main() {
    print_all(1, 2, 3);
}
```

程序的输出是？

A. `1 2 3`（带空格）
B. `123`（无分隔符）
C. `321`（逆序）
D. 编译错误

## Explanation

正确答案是 B，即 `123`（无分隔符）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。模板题要区分编译期实例化、类型推导、特化/重载匹配和 SFINAE/约束；不要把模板当作运行时多态。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
