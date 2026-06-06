---
qid: cpp-algo-r-005
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: "B"
---

### 题目

以下代码输出什么？

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto it = std::find_if(v.begin(), v.end(), [](int x){ return x > 25; });
    if (it != v.end()) {
        std::cout << "找到: " << *it << std::endl;
    } else {
        std::cout << "未找到" << std::endl;
    }
}
```

A. `找到: 20`
B. `找到: 30`
C. `找到: 50`
D. `未找到`

## Explanation

`std::find_if` 返回第一个满足谓词的元素的迭代器。从左到右扫描，`10 <= 25`，`20 <= 25`，`30 > 25` ——找到 `30`，返回指向它的迭代器。`it != v.end()` 为真，输出 `找到: 30`。
