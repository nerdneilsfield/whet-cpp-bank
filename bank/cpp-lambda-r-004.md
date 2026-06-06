---
qid: cpp-lambda-r-004
type: single
kp: [cpp-lambdas]
difficulty: easy
answer_key: B
---

### 题目

下面代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5};
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
```

A. 输出：`1 1 3 4 5`
B. 输出：`5 4 3 1 1`
C. 编译错误：lambda 不能作为比较器
D. 输出：`3 1 4 1 5`（原始顺序不变）

## Explanation

B


正确答案是 B。传给 `std::sort` 的 lambda 返回 `a > b`，表示较大的元素应排在较小元素前面，因此排序结果是降序 `5 4 3 1 1`。A 项是默认升序排序的结果；C 项错误，lambda 可以作为满足比较器要求的可调用对象；D 项忽略了 `std::sort` 会原地重排容器元素。
