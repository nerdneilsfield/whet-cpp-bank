---
qid: cpp-func-024
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: A
---

下列代码中，`foo` 函数原型写在 `main` 之前，定义写在之后。编译结果是？

```cpp
#include <iostream>
int foo(int x);          // 原型
int main() {
    std::cout << foo(5);
}
int foo(int x) { return x * 3; }
```

A. 正常编译并输出 `15`
B. 编译错误：`foo` 未定义
C. 运行时错误
D. 输出 `5`

## Explanation

正确答案是 A，对应“正常编译并输出 15”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“编译错误：foo 未定义”不满足题干要求；C 项“运行时错误”不满足题干要求；D 项“输出 5”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
