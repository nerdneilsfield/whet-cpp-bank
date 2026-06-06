---
qid: cpp-func-017
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: B
---

以下代码每次调用 `counter()` 输出什么序列（连续调用三次）？

```cpp
void counter() {
    static int cnt = 0;
    cnt++;
    std::cout << cnt << " ";
}
```

A. `0 0 0`
B. `1 2 3`
C. `1 1 1`
D. 编译错误

## 解析

正确答案是 B，对应“1 2 3”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“0 0 0”不满足题干要求；C 项“1 1 1”不满足题干要求；D 项“编译错误”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
