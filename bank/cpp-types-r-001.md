---
qid: cpp-types-r-001
type: single
kp: [cpp-types]
difficulty: easy
answer_key: B
---

# 代码阅读：auto 推导 initializer_list

下列代码能否编译？若能，`x` 的类型是什么？

```cpp
#include <initializer_list>
auto x = {1, 2, 3};
```

A. 编译错误：无法从花括号列表推导 `auto`  
B. 编译成功；`x` 的类型是 `std::initializer_list<int>`  
C. 编译成功；`x` 的类型是 `int[3]`  
D. 编译成功；`x` 的类型是 `std::vector<int>`
