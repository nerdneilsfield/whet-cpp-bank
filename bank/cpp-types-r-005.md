---
qid: cpp-types-r-005
type: single
kp: [cpp-types]
difficulty: easy
answer_key: C
---

# 代码阅读：constexpr 在运行时使用

```cpp
#include <iostream>
constexpr int square(int n) { return n * n; }

int main() {
    int x;
    std::cin >> x;
    std::cout << square(x) << "\n";
}
```

以下说法哪个**正确**？

A. 编译错误：`constexpr` 函数不能接收运行时参数  
B. 编译错误：`square(x)` 必须在编译期求值  
C. 编译成功，运行时正常输出 `x` 的平方；`constexpr` 函数在参数非常量时退化为普通函数  
D. 编译成功，但 `square(x)` 始终返回 `0`（运行时未计算）
