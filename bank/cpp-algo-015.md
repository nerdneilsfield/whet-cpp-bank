---
qid: cpp-algo-015
type: fill
kp: [cpp-algorithms]
difficulty: easy
answer_key: "{1, 2, 4, 5}"
---

以下代码执行后，`v` 的逻辑内容（有效元素）是 `______`。

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto new_end = std::remove(v.begin(), v.end(), 3);
    v.erase(new_end, v.end());
}
```

## 解析

答案是 `{1, 2, 4, 5}`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
