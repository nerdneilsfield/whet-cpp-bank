---
qid: cpp-fp-018
type: fill
kp: [cpp-function-pointers]
difficulty: easy
answer_key: "std::bind(multiply, 3, std::placeholders::_1)"
---

# 代码填空：`std::bind` 绑定部分参数

```cpp
#include <functional>

int multiply(int a, int b) { return a * b; }

// 用 std::bind 创建一个"将第一个参数固定为 3"的单参数可调用对象
std::function<int(int)> triple = ________;
// triple(7) 应返回 21
```

填写 `________` 处的表达式（不含分号）。

## Explanation

应填写 `std::bind(multiply, 3, std::placeholders::_1)`。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
