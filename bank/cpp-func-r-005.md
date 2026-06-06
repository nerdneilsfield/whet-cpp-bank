---
qid: cpp-func-r-005
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

# 代码阅读：无终止条件的递归

以下代码运行后会发生什么？

```cpp
#include <iostream>
int sum(int n) {
    return n + sum(n - 1);  // 没有 base case
}
int main() {
    std::cout << sum(5);
    return 0;
}
```

A. 输出 `15`
B. 输出 `0`
C. 运行时栈溢出（stack overflow），程序崩溃
D. 编译失败，编译器检测到无限递归

## Explanation

正确答案是 C，对应“运行时栈溢出（stack overflow），程序崩溃”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“输出 15”不满足题干要求；B 项“输出 0”不满足题干要求；D 项“编译失败，编译器检测到无限递归”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
