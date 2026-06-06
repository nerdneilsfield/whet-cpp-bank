---
qid: cpp-algo-017
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码执行后，`dst` 的内容是什么？

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst;
    std::copy_if(src.begin(), src.end(), std::back_inserter(dst),
                 [](int x) { return x > 3; });
}
```

A. `{1, 2, 3}`
B. `{4, 5}`
C. `{1, 2, 3, 4, 5}`
D. `{}`

## 解析

正确答案是 B。`std::copy_if` 会把满足谓词 `x > 3` 的元素复制到输出迭代器位置；输入中只有 `4` 和 `5` 满足条件。`std::back_inserter(dst)` 会调用 `push_back` 扩展空向量。
