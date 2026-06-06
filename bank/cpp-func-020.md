---
qid: cpp-func-020
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

以下代码输出什么？

```cpp
int f(int x, int y = 10) { return x + y; }
int main() {
    std::cout << f(3) << " " << f(3, 4);
}
```

A. `3 7`
B. `10 4`
C. `13 7`
D. 编译错误

## Explanation

正确答案是 C，对应“13 7”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“3 7”不满足题干要求；B 项“10 4”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
