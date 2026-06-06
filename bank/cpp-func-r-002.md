---
qid: cpp-func-r-002
type: single
kp: [cpp-functions]
difficulty: easy
answer_key: C
---

# 代码阅读：重载解析歧义

以下代码能否编译通过？

```cpp
#include <iostream>
void print(int x)  { std::cout << "int"; }
void print(long x) { std::cout << "long"; }

int main() {
    print(42);   // 42 是 int 字面量，没有问题
    print(42L);  // 42L 是 long 字面量，没有问题
    print('A');  // char 可隐式转换为 int 或 long，两个重载同样匹配
    return 0;
}
```

A. 编译通过，输出 `intlongint`
B. 编译通过，输出 `intlonglong`
C. 编译失败，`print('A')` 调用产生歧义，无法确定最佳重载
D. 运行时未定义行为

## Explanation

正确答案是 C，对应“编译失败，print('A') 调用产生歧义，无法确定最佳重载”。本题考查 iostream/文件流/格式化输出的状态与缓冲规则，关键是区分格式控制、流状态和实际写入时机。其他选项容易混淆相关概念：A 项“编译通过，输出 intlongint”不满足题干要求；B 项“编译通过，输出 intlonglong”不满足题干要求；D 项“运行时未定义行为”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
