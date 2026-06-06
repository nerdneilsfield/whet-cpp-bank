---
qid: cpp-enum-010
type: single
kp: [cpp-enum]
difficulty: easy
answer_key: D
---
以下代码是否合法？

```cpp
enum A { X, Y };
enum B { X, Z };   // X 在同一命名空间内重复定义
```

A. 合法，两个 X 属于不同枚举，不冲突
B. 合法，仅发出警告
C. 合法，后者覆盖前者
D. 编译错误：传统 enum 的枚举器直接注入外层命名空间，`X` 重定义
