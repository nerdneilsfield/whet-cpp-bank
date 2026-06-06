---
qid: cpp-func-015
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: D
---

以下代码输出什么？

```cpp
void greet() {
    std::cout << "Hello";
    return;
    std::cout << "World";
}
int main() { greet(); }
```

A. `HelloWorld`
B. `World`
C. 编译错误，`void` 函数不能有 `return`
D. `Hello`

## 解析

正确答案是 D，对应“Hello”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“HelloWorld”不满足题干要求；B 项“World”不满足题干要求；C 项“编译错误，void 函数不能有 return”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
