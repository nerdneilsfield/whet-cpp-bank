---
qid: cpp-func-r-001
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

# 代码阅读：默认参数顺序错误

以下代码能否编译通过？

```cpp
#include <iostream>
void greet(std::string name = "World", std::string prefix) {
    std::cout << prefix << " " << name;
}
int main() {
    greet("Alice", "Hello");
    return 0;
}
```

A. 编译通过，输出 `Hello Alice`
B. 编译通过，输出 `World Hello`
C. 编译失败，有默认值的参数必须在参数列表末尾
D. 运行时错误

## Explanation

正确答案是 C，对应“编译失败，有默认值的参数必须在参数列表末尾”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“编译通过，输出 Hello Alice”不满足题干要求；B 项“编译通过，输出 World Hello”不满足题干要求；D 项“运行时错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
