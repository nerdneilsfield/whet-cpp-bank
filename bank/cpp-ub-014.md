---
qid: cpp-ub-014
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# strict aliasing 简单例子

```cpp
int i = 0x3F800000;  // IEEE 754 表示 1.0f
float f = *(float*)&i;   // 通过 float* 读取 int 存储
```

上述代码（在非 `char*` 路径下）：

A. 保证合法，`int` 和 `float` 大小相同所以可以互转
B. 编译错误，C++ 不允许此类指针转型
C. 违反 strict aliasing 规则，属于未定义行为；正确做法是用 `memcpy` 或 `std::bit_cast`
D. 合法，只要结果在 `float` 的可表示范围内
