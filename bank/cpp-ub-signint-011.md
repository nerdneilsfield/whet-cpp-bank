---
qid: cpp-ub-signint-011
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# `short` 参与算术自动提升为 `int`

下面代码中，哪个断言**不会**失败（即为真）？

```cpp
#include <iostream>
#include <type_traits>
int main() {
    short a = 1000;
    short b = 2000;
    auto  c = a + b;

    // 以下哪条为 true？
    bool t1 = std::is_same_v<decltype(c), short>;   // A 的反面
    bool t2 = std::is_same_v<decltype(c), int>;     // B
    bool t3 = (sizeof(c) == sizeof(short));          // C
    bool t4 = std::is_same_v<decltype(c), long>;    // D

    std::cout << t1 << t2 << t3 << t4 << std::endl;
    return 0;
}
```

输出的四个值中，哪一个为 `1`？

A. `t2`（`decltype(c)` 是 `int`）
B. `t1`（`decltype(c)` 是 `short`）
C. `t3`（`sizeof(c) == sizeof(short)`）
D. `t4`（`decltype(c)` 是 `long`）

> **知识点**：`short` 参与算术运算时被**整数提升**为 `int`。因此 `a + b` 的结果类型是 `int`，`sizeof(c)` 为 4（而非 2）。`t2` 为真，输出 `0100`。
