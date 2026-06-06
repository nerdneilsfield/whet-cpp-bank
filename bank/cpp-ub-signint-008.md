---
qid: cpp-ub-signint-008
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# signed/unsigned 混合算术的提升规则

下面代码的输出是什么？

```cpp
#include <iostream>
int main() {
    int    a = -3;
    unsigned int b = 1u;
    auto   c = a + b;   // c 的类型是什么？值是什么？
    std::cout << c << std::endl;
    return 0;
}
```

A. `-2`（int 类型，-3 + 1 = -2）
B. 未定义行为
C. `4294967294`（unsigned int，`(UINT_MAX+1) - 3 + 1 = UINT_MAX - 1`）
D. 编译错误

> **知识点**：当 `int` 与 `unsigned int` 混合运算时，**通常算术转换（Usual Arithmetic Conversions）**规定：`int` 被提升为 `unsigned int`。`-3` 转为 `unsigned int` 变为 `4294967293`，加 `1` 得 `4294967294`。结果类型为 `unsigned int`，而非 `int`。`auto c` 会推导为 `unsigned int`。
