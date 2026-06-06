---
qid: cpp-func-r-004
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: A
---

# 代码阅读：值传递不影响原变量

阅读以下代码，推断输出结果：

```cpp
#include <iostream>
void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int main() {
    int x = 10, y = 20;
    swap(x, y);
    std::cout << x << " " << y;
    return 0;
}
```

A. `10 20`
B. `20 10`
C. `0 0`
D. 编译错误

## 解析

正确答案是 A，对应“10 20”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“20 10”不满足题干要求；C 项“0 0”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
