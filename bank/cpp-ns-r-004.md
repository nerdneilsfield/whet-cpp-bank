---
qid: cpp-ns-r-004
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

# 代码阅读：__cplusplus 宏的值与 C++ 版本

下列代码在以 C++17 标准编译时（`-std=c++17`）输出什么？

```cpp
#include <iostream>

int main() {
    std::cout << __cplusplus << std::endl;
}
```

A. `2017`  
B. `201703L`（即整数值 `201703`）  
C. `17`  
D. `1`（仅表示"是 C++ 编译器"，不区分版本）

## Explanation

正确答案是 B，因为该选项对应 ``201703L`（即整数值 `201703`）`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
