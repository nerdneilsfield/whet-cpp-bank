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
