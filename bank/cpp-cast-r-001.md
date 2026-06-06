---
qid: cpp-cast-r-001
type: single
kp: [cpp-casting]
difficulty: easy
answer_key: B
---

### 题目

下面代码的输出是什么？

```cpp
#include <iostream>

int main() {
    double x = 3.9;
    int a = static_cast<int>(x);
    int b = static_cast<int>(-3.9);
    std::cout << a << " " << b << std::endl;
    return 0;
}
```

A. `4 -4`（四舍五入）
B. `3 -3`（向零截断）
C. `3 -4`（向下取整）
D. 编译错误

## Explanation

B


`static_cast<int>` 将浮点数转换为整数时执行**向零截断**（truncation toward zero），不是四舍五入，也不是向下取整。`3.9` 截断得 `3`，`-3.9` 截断得 `-3`（不是 `-4`）。这是 C++ 标准规定的行为，与 `(int)` C 风格转换等价。
