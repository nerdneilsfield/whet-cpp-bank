---
qid: cpp-types-r-003
type: single
kp: [cpp-types]
difficulty: easy
answer_key: B
---

# 代码阅读：列表初始化窄化转换

以下代码能否编译通过？

```cpp
double d = 3.14;
int x{d};
```

A. 编译成功，`x == 3`（隐式截断）  
B. 编译错误（或强制诊断）：列表初始化不允许窄化转换  
C. 编译成功，`x == 3.14`（double 存入 int）  
D. 运行时抛出异常
