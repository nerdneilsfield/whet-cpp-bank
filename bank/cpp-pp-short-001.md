---
qid: cpp-pp-short-001
type: short
kp: [cpp-preprocessor]
difficulty: medium
rubric:
  - 解释 #include guard 或 #pragma once 防止同一头文件在一个翻译单元被重复包含
  - 给出标准写法：#ifndef X / #define X / #endif
  - 对比 #pragma once 简洁但非标准（实际广泛支持）
  - 提到不防护会导致重复定义错误
---
请解释为什么 C++ 头文件需要包含保护（include guard），以及常见的两种写法。

---

**参考答案：**

如果一个头文件在同一翻译单元里被多次 `#include`（直接或间接），其中的类型/函数/变量定义会重复出现，导致编译错误（重定义）或链接错误。包含保护用于让头文件即使被多次包含，实际内容也只展开一次。两种常见写法：一是传统宏守卫——

```cpp
#ifndef MY_HEADER_H
#define MY_HEADER_H
// ...
#endif
```

二是 `#pragma once`，由编译器层面做"同一文件只处理一次"判断，写法简洁，但不是 C++ 标准（实际所有主流编译器都支持）。两者也可以同时写以兼顾兼容性。

## Explanation

作答应围绕：解释 #include guard 或 #pragma once 防止同一头文件在一个翻译单元被重复包含；给出标准写法：#ifndef X / #define X / #endif；对比 #pragma once 简洁但非标准（实际广泛支持）。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 短答题不要只给结论，还要说明为什么这些规则会导致相应行为，并指出容易混淆的反例或边界情况。
