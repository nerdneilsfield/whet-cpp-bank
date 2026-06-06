---
qid: cpp-stl-r-003
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

# 代码阅读：vector 初始化内容

下列代码输出什么？

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v(3, 5);
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
```

A. `5 5 5`  
B. `3 5 0`  
C. `0 0 0`（值初始化忽略第二个参数）  
D. 编译错误：`vector<int>` 构造函数不接受两个整型参数

## Explanation

正确答案是 A，即 `5 5 5`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
