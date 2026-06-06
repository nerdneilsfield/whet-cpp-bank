---
qid: cpp-algo-012
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: A
---

以下代码执行后，`out` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> out(5);
    std::transform(src.begin(), src.end(), out.begin(),
                   [](int x) { return x * x; });
}
```

A. `{1, 4, 9, 16, 25}`
B. `{1, 2, 3, 4, 5}`
C. `{2, 4, 6, 8, 10}`
D. `{0, 0, 0, 0, 0}`

## Explanation

正确答案为 A，因为“`{1, 4, 9, 16, 25}`”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
