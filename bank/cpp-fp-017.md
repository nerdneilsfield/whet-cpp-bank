---
qid: cpp-fp-017
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: A
---

# 代码阅读：`std::function` 存储有捕获 lambda

```cpp
#include <iostream>
#include <functional>

int main() {
    int offset = 100;
    std::function<int(int)> f = [offset](int x) { return x + offset; };
    std::cout << f(5);
}
```

输出是？

A. 105  
B. 编译错误：有捕获 lambda 不能存入 `std::function`  
C. 100  
D. 5

## Explanation

正确答案是 A，对应“105”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“编译错误：有捕获 lambda 不能存入 std::function”不满足题干要求；C 项“100”不满足题干要求；D 项“5”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
