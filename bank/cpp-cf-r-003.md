---
qid: cpp-cf-r-003
type: single
kp: [cpp-control-flow]
difficulty: easy
answer_key: C
---

# 代码阅读：for 循环变量作用域

以下代码能否编译通过？

```cpp
#include <iostream>
int main() {
    for (int i = 0; i < 3; i++) {
        std::cout << i;
    }
    std::cout << i;  // 使用循环变量
    return 0;
}
```

A. 编译通过，输出 `0123`
B. 编译通过，输出 `012` 后打印未定义值
C. 编译失败，`i` 在循环外不可见
D. 运行时错误

## Explanation

正确答案为 C，因为“编译失败，`i` 在循环外不可见”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。控制流题要按条件判断、循环边界、短路求值和跳转语句的实际执行顺序推演。
