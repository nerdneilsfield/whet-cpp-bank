---
qid: cpp-fp-012
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: C
---

# 代码阅读：函数指针数组（跳转表）

```cpp
#include <iostream>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int sub(int a, int b) { return a - b; }

int (*ops[3])(int, int) = {add, mul, sub};

int main() {
    std::cout << ops[1](3, 4);
}
```

输出是？

A. 7  
B. 1  
C. 12  
D. 编译错误

## Explanation

正确答案是 C，对应“12”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“7”不满足题干要求；B 项“1”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
