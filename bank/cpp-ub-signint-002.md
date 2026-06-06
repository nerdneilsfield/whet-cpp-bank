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

## Explanation

填入 `18446744073709551611`，因为题目要求的是该规则下的精确表达或标准名称。未定义行为题的关键是区分“标准无保证”和“某次运行看起来正常”；一旦触发 UB，编译器可基于其不会发生来优化。 常见误区是写出近似说法、旧式写法或省略必要的命名空间/符号，导致与答案含义不完全一致。
