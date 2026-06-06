---
qid: cpp-cpp11-011
type: single
kp: [cpp-cpp11]
difficulty: easy
answer_key: A
---

# 代码阅读：范围 for 修改元素

阅读以下代码，输出是什么？

```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 3};
    for (auto& x : v) {
        x *= 2;
    }
    for (auto x : v) {
        std::cout << x << " ";
    }
}
```

A. `2 4 6`
B. `1 2 3`
C. 编译错误
D. 未定义行为

## Explanation

正确答案是 A。`auto` 按模板实参推导规则工作，常会丢弃顶层 `const` 和引用，除非显式写成 `auto&`。选项 A 的表述“｀2 4 6｀”正好符合该规则。B、C、D 的问题通常在于把相近概念混同、忽略默认行为，或把运行期现象误认为编译期/标准规定。
