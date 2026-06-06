---
qid: cpp-algo-011
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码的输出是什么？

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int cnt = std::count(v.begin(), v.end(), 3);
    std::cout << cnt << std::endl;
}
```

A. 0
B. 1
C. 3
D. 5

## 解析

正确答案为 B，因为“1”符合题干所问的 C++ 规则或代码执行结果。A、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
