---
qid: cpp-algo-013
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: D
---

以下代码执行后，`v` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::reverse(v.begin(), v.end());
}
```

A. `{1, 2, 3, 4, 5}`
B. `{5, 4, 3, 2, 1, 1, 2, 3, 4, 5}`
C. `{1, 5, 2, 4, 3}`
D. `{5, 4, 3, 2, 1}`

## 解析

正确答案为 D，因为“`{5, 4, 3, 2, 1}`”符合题干所问的 C++ 规则或代码执行结果。A、B、C 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
