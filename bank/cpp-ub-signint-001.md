---
qid: cpp-ub-signint-001
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: A
---

# 有符号/无符号比较：`-1 > 2u` 的结果

下面代码的输出是什么？

```cpp
#include <iostream>
int main() {
    int a = -1;
    unsigned int b = 2u;
    std::cout << (a > b) << std::endl;
    return 0;
}
```

A. `1`（即 true）
B. `0`（即 false）
C. 未定义行为，结果不可预测
D. 编译错误

> **知识点**：有符号与无符号整数混合比较时，有符号操作数会被**隐式转换为无符号类型**。`-1` 转为 `unsigned int` 后变为 `UINT_MAX`（4294967295），远大于 `2u`，因此比较结果为 `true`（1）。
