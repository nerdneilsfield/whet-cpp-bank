---
qid: cpp-ub-008
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# 有符号整数溢出

```cpp
#include <climits>
int main() {
    int x = INT_MAX;
    int y = x + 1;   // 此行
    return 0;
}
```

标注行的行为是：

A. `y` 等于 `INT_MIN`，有符号溢出定义为回绕
B. 编译错误，编译器禁止溢出表达式
C. 未定义行为，编译器可假设溢出不发生并据此优化
D. 运行时会抛出 `std::overflow_error`
