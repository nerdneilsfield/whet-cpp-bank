---
qid: cpp-ns-r-002
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: A
---

# 代码阅读：宏不做类型检查

下列代码能否编译？输出什么？

```cpp
#include <iostream>
#define DOUBLE(x) ((x) + (x))

int main() {
    std::string s = "ab";
    std::cout << DOUBLE(s) << std::endl;
}
```

A. 编译成功，输出 `abab`（宏对 `std::string` 展开为字符串拼接，不做类型检查）  
B. 编译错误：宏只能作用于数值类型  
C. 编译成功，输出 `ab ab`（自动在中间插入空格）  
D. 运行时抛出异常：`string` 不支持 `+` 运算符

## 解析

正确答案是 A，因为该选项对应 `编译成功，输出 `abab`（宏对 `std::string` 展开为字符串拼接，不做类型检查）`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 B 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
