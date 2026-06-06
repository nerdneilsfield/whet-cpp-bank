---
qid: cpp-ub-012
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: D
---

# 悬空引用

```cpp
#include <iostream>
int& get() {
    int local = 10;
    return local;   // 返回局部变量的引用
}
int main() {
    int& r = get();
    std::cout << r;
}
```

上述代码：

A. 编译错误，编译器禁止返回局部变量引用
B. 输出 10，局部变量在函数返回后仍有效
C. 运行时抛出异常，属于可预测错误
D. 未定义行为，`r` 是悬空引用，访问它后果不可预测
