---
qid: cpp-ns-r-003
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: C
---

# 代码阅读：头文件重复包含导致重复定义

假设 `point.h` 内容如下（**没有** include guard）：

```cpp
// point.h
struct Point { int x, y; };
```

main.cpp 如下：

```cpp
#include "point.h"
#include "point.h"  // 重复包含

int main() {}
```

编译会发生什么？

A. 正常编译：编译器自动去重，忽略重复的 `#include`  
B. 运行时错误：重复定义在链接阶段才会报错  
C. 编译错误：`struct Point` 被定义了两次，违反 ODR（One Definition Rule）  
D. 编译警告，但不影响运行
