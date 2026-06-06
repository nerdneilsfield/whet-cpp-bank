---
qid: cpp-ns-r-004
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

# 代码阅读：__cplusplus 宏的值与 C++ 版本

下列代码在以 C++17 标准编译时（`-std=c++17`）输出什么？

```cpp
#include <iostream>

int main() {
    std::cout << __cplusplus << std::endl;
}
```

A. `2017`  
B. `201703L`（即整数值 `201703`）  
C. `17`  
D. `1`（仅表示"是 C++ 编译器"，不区分版本）
