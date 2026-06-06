---
qid: cpp-func-011
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: A
---

下列递归函数计算阶乘，`factorial(3)` 的返回值是多少？

```cpp
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

A. `6`
B. `3`
C. `9`
D. `1`

## Explanation

正确答案是 A，对应“6”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：B 项“3”不满足题干要求；C 项“9”不满足题干要求；D 项“1”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
