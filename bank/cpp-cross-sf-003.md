---
qid: cpp-cross-sf-003
type: single
kp: [cpp-scope-linkage, cpp-functions]
difficulty: easy
answer_key: C
---

关于以下场景，正确的说法是哪一项？

```
// math_utils.h
#pragma once

inline int square(int x) {
    return x * x;
}
```

```
// a.cpp
#include "math_utils.h"
// uses square()
```

```
// b.cpp
#include "math_utils.h"
// uses square()
```

A. 违反 ODR，链接时报 "multiple definition of square" 错误  
B. 每个翻译单元各生成一份外部链接的 square，链接器会报重复符号  
C. 合法：inline 函数允许在多个翻译单元中出现相同定义，不违反 ODR  
D. 合法，但 square 必须声明为 static 才能在多个文件中使用

<!--
C++ ODR 对 inline 函数有豁免：同一 inline 函数定义可出现在多个翻译单元中，
只要每份定义相同。编译器/链接器会折叠重复定义，不产生多重定义错误。
inline 函数具有外部链接但 ODR 允许其多定义，这正是头文件中定义 inline 函数
的标准做法。
-->
