---
qid: cpp-ns-002
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: C
---

以下头文件保护写法正确的是？

A.
```cpp
#pragma ifndef
#define MYHEADER_H
// ...
#endif
```
B.
```cpp
#ifndef MYHEADER_H
// ...
#endif
```
C.
```cpp
#ifndef MYHEADER_H
#define MYHEADER_H
// ...
#endif
```
D.
```cpp
#ifdef MYHEADER_H
#define MYHEADER_H
// ...
#endif
```

## 解析

本题应根据答案键 `C` 判断。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 作答时要把规则和题干中的具体代码或描述对应起来，避免只凭表面形式选择。
