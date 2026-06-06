---
qid: cpp-ub-signint-002
type: fill
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: 18446744073709551611
---

# `size_t` 减法下溢

下面代码中，`result` 的值是多少（64位系统，`size_t` 为 64位无符号整数）？

```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};  // size() == 5
    size_t result = v.size() - 10;
    std::cout << result << std::endl;
    return 0;
}
```

请填写 `result` 的输出值：`______`

> **知识点**：`v.size()` 返回 `size_t`（无符号类型），值为 5。`5 - 10` 在无符号算术下发生**下溢（wrap-around）**，结果为 `2^64 - 5 = 18446744073709551611`，而非 `-5`。这是常见 bug 来源，尤其在循环边界检查中。
