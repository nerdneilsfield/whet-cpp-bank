---
qid: cpp-types-med-001
type: single
kp: [cpp-types]
difficulty: medium
answer_key: C
---
下列代码输出结果是？

```cpp
#include <iostream>
int main() {
    unsigned int a = 1;
    int b = -2;
    std::cout << (a + b) << "\n";
    return 0;
}
```

A. -1
B. 编译错误
C. 4294967295
D. 未定义行为

---

**解析：**

这是典型的整型提升与符号转换陷阱。当 `int` 与 `unsigned int` 进行算术运算时，根据“通常算术转换”规则，`int` 操作数会被转换为 `unsigned int`。`-2` 被转换为 `unsigned int` 得到 `4294967294`，再加 `1` 得到 `4294967295`。整个过程是良好定义的（无符号溢出按模 2^N 运算），不是 UB。
