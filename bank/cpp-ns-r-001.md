---
qid: cpp-ns-r-001
type: single
kp: [cpp-preprocessor]
difficulty: easy
answer_key: B
---

# 代码阅读：函数宏缺括号导致优先级错误

下列代码输出什么？

```cpp
#include <iostream>
#define SQ(x) x * x

int main() {
    std::cout << SQ(1 + 2) << std::endl;
}
```

A. `9`（`(1+2)*(1+2) = 9`）  
B. `5`（宏展开为 `1 + 2 * 1 + 2 = 5`，乘法优先级高于加法）  
C. `7`  
D. 编译错误：宏参数不能包含 `+`

## Explanation

正确答案是 B，因为该选项对应 ``5`（宏展开为 `1 + 2 * 1 + 2 = 5`，乘法优先级高于加法）`，符合题中代码或概念的 C++ 语义。预处理题要记住宏在编译前做文本替换，条件编译和 include guard 也都发生在语义分析之前。常见误区是把宏当成有类型的函数，或忽略宏参数重复求值和括号不足带来的副作用。 A 项、C 项、D 项 的问题在于忽略了上述规则中的一个关键条件，因此会得到看似合理但错误的结论。
