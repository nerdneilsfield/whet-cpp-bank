---
qid: cpp-stl-r-002
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: B
---

# 代码阅读：string::find 返回 npos 的处理

下列代码输出什么？

```cpp
#include <string>
#include <iostream>

int main() {
    std::string s = "hello world";
    size_t pos = s.find("xyz");
    if (pos == std::string::npos) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found at " << pos << std::endl;
    }
}
```

A. `found at 18446744073709551615`（因为 `npos` 是 `size_t` 最大值）  
B. `not found`  
C. 编译错误：`size_t` 与 `std::string::npos` 类型不匹配，不能用 `==` 比较  
D. 运行时抛出 `std::out_of_range` 异常

## 解析

正确答案是 B，即 `not found`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
