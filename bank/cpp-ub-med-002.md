---
qid: cpp-ub-med-002
type: single
kp: [cpp-undefined-behavior]
difficulty: medium
answer_key: C
---
下列代码的行为是？

```cpp
#include <iostream>
int main() {
    int x;
    if (x == 0) std::cout << "zero";
    else        std::cout << "nonzero";
    return 0;
}
```

A. 一定输出 "zero"，因为静态/局部变量默认初始化为 0
B. 一定输出 "nonzero"
C. 未定义行为：读取未初始化的自动变量
D. 编译器会拒绝编译

---

**解析：**

只有具有静态/线程存储期的对象才会被默认零初始化；具有自动存储期的局部变量在没有初始化器时是“默认初始化”，对于内建类型来说**不进行任何初始化**，其值是不确定的（indeterminate value）。读取不确定值在多数情况下是未定义行为（UB）——可能读到任意垃圾、可能让编译器以为不可达从而做激进优化，也可能在某些平台触发陷阱表示。优化器经常据此删除整段代码或两边都打印。务必显式初始化 `int x = 0;`。
