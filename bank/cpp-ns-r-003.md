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

## Explanation

正确答案是 C，因为该选项对应 `编译错误：`struct Point` 被定义了两次，违反 ODR（One Definition Rule）`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、B 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
