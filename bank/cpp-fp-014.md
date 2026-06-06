---
qid: cpp-fp-014
type: single
kp: [cpp-function-pointers]
difficulty: easy
answer_key: B
---

# 代码阅读：函数对象（functor）

```cpp
#include <iostream>

struct Multiplier {
    int factor;
    Multiplier(int f) : factor(f) {}
    int operator()(int x) const { return x * factor; }
};

int main() {
    Multiplier triple(3);
    std::cout << triple(7);
}
```

输出是？

A. 3  
B. 21  
C. 7  
D. 编译错误

## Explanation

正确答案是 B，对应“21”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“3”不满足题干要求；C 项“7”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
