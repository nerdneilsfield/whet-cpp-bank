---
qid: cpp-algo-014
type: fill
kp: [cpp-algorithms]
difficulty: easy
answer_key: "4"
---

以下代码执行后，`cnt` 的值是 `______`。

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    int cnt = std::count_if(v.begin(), v.end(),
                            [](int x) { return x % 2 == 0; });
}
```

## 解析

答案是 `4`。题干要求填写的是能直接满足语法、命令或代码执行结果的精确文本，其他近似写法通常会改变含义或无法通过严格匹配。常见误区是把相关概念写成解释性短语，或忽略空格、符号、大小写等细节。STL 算法通常只操作迭代器区间，前置条件、返回值和是否改变容器大小要分开判断。
