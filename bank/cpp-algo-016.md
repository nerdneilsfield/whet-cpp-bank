---
qid: cpp-algo-016
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: C
---

以下代码的输出是什么？

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    auto it = std::min_element(v.begin(), v.end());
    std::cout << *it << std::endl;
}
```

A. 3
B. 9
C. 1
D. 4

## Explanation

正确答案为 C，因为“1”符合题干所问的 C++ 规则或代码执行结果。A、B、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
