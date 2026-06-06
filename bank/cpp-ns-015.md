---
qid: cpp-ns-015
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

以下哪段代码使用了**嵌套命名空间**？

A.
```cpp
namespace A {}
namespace B {}
```
B.
```cpp
namespace Outer {
    namespace Inner {
        void foo();
    }
}
```
C.
```cpp
namespace A = B;
```
D.
```cpp
using namespace std;
```

## 解析

本题应根据答案键 `B` 判断。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 作答时要把规则和题干中的具体代码或描述对应起来，避免只凭表面形式选择。
