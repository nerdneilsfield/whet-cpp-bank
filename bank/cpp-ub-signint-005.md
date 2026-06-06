---
qid: cpp-ub-signint-005
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 4294967295
---

# `-1` 转换为 `unsigned int` 的值

下面代码输出什么（32位 `unsigned int`，`UINT_MAX = 4294967295`）？

```cpp
#include <iostream>
int main() {
    int a = -1;
    unsigned int b = static_cast<unsigned int>(a);
    std::cout << b << std::endl;
    return 0;
}
```

请填写输出值：`______`

> **知识点**：将 `-1`（有符号）转换为 `unsigned int` 时，C++ 标准规定结果为 `2^N - 1`（N=32 时即 `4294967295`）。这是**定义良好**的行为，但在比较中经常造成逻辑 bug。例如 `-1 > 2u` 为真，就是因为 `-1` 被视为 `4294967295`。

## 解析

填入 `4294967295`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
