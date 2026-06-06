---
qid: cpp-stl-r-004
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

# 代码阅读：map operator[] 对不存在的 key 插入默认值

下列代码输出什么？

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> m;
    m["a"] = 1;
    std::cout << m["b"] << std::endl;  // "b" 不存在
    std::cout << m.size() << std::endl;
}
```

A. 运行时抛出 `std::out_of_range` 异常  
B. 输出 `0` 和 `1`（`size` 不变，仅读取默认值）  
C. 输出 `0` 和 `2`（`operator[]` 插入了键 `"b"`，值默认初始化为 `0`）  
D. 编译错误：`map` 下标访问不存在的键是非法的

## Explanation

正确答案是 C，即 输出 `0` 和 `2`（`operator[]` 插入了键 `"b"`，值默认初始化为 `0`）。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
