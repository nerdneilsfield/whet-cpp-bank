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
