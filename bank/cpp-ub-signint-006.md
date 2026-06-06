---
qid: cpp-ub-signint-006
type: single
kp: [cpp-undefined-behavior]
difficulty: easy
answer_key: C
---

# `std::vector::size()` 与负数 `int` 比较的陷阱

下面代码的 `if` 分支会执行吗？

```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {10, 20, 30};
    int n = -1;
    if (n < (int)v.size()) {
        std::cout << "safe branch" << std::endl;
    } else {
        std::cout << "unreachable?" << std::endl;
    }
    return 0;
}
```

注意：此处已加了 `(int)` 强制转换。若**去掉** `(int)` 转换，即写成 `if (n < v.size())`，结果会变成什么？

A. 结果不变，仍输出 `safe branch`
B. 编译错误
C. 输出 `unreachable?`（`n` 提升为无符号后变大数）
D. 未定义行为，崩溃

> **知识点**：去掉 `(int)` 后，`n`（值为 -1）与 `v.size()`（`size_t`）比较，`n` 被提升为 `size_t`，变为 `SIZE_MAX`（极大正数），大于 3，导致比较结果为 false，执行 else 分支。加 `(int)` 转换后逻辑正确，因为 -1 < 3。
