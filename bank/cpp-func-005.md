---
qid: cpp-func-005
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

以下代码执行后，`a` 的值是多少？

```cpp
void doubleIt(int& x) { x *= 2; }
int main() {
    int a = 5;
    doubleIt(a);
    std::cout << a;
}
```

A. `5`
B. `10`
C. `25`
D. 编译错误

## 解析

正确答案是 B，对应“10”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“5”不满足题干要求；C 项“25”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
