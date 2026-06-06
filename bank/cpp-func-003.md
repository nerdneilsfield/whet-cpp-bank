---
qid: cpp-func-003
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

以下代码输出什么？

```cpp
int square(int x) { return x * x; }
int main() { std::cout << square(4); }
```

A. `4`
B. `8`
C. `16`
D. 编译错误

## Explanation

正确答案是 C，对应“16”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“4”不满足题干要求；B 项“8”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
