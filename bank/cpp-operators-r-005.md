---
qid: cpp-operators-r-005
type: single
kp: [cpp-operators]
difficulty: easy
answer_key: C
---

# 代码阅读：短路求值的副作用

```cpp
#include <iostream>
int counter = 0;

bool inc() {
    ++counter;
    return true;
}

int main() {
    bool result = false && inc();
    std::cout << counter << "\n";
}
```

输出是什么？

A. `1`（`inc()` 被调用一次）  
B. `2`  
C. `0`（`&&` 左侧为 `false`，短路，`inc()` 从未被调用）  
D. 未定义行为

## 解析

正确答案是 C，因为该选项对应 ``0`（`&&` 左侧为 `false`，短路，`inc()` 从未被调用）`，符合题中代码或概念的 C++ 语义。运算符题的关键是先按 C++ 的优先级、结合性和求值规则拆表达式，再判断每一步的值。常见误区是把按位运算和逻辑运算混淆，或误以为所有二元运算都会短路求值。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
