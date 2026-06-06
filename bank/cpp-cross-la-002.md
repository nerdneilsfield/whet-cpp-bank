---
qid: cpp-cross-la-002
type: single
kp: [cpp-lambdas, cpp-algorithms]
difficulty: easy
answer_key: B
---

以下代码输出是什么？

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 3, 7, 4, 9, 2};
    auto it = std::find_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    });
    if (it != v.end()) {
        std::cout << *it << std::endl;
    }
    return 0;
}
```

A. 2  
B. 4  
C. 7  
D. 9

<!--
find_if 从左到右找第一个满足 x%2==0 的元素：1(奇)、3(奇)、7(奇)、4(偶) → 返回指向 4 的迭代器，*it = 4。
-->

## Explanation

B 正确：`std::find_if` 从左到右查找第一个满足谓词的元素。谓词判断偶数，序列中 1、3、7 都不满足，第一个满足的是 4，而不是后面的 2。关键误区是把“查找偶数”理解成查找最小偶数；算法只返回第一个匹配项，不会继续扫描优化答案。
