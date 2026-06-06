---
qid: cpp-algo-r-001
type: single
kp: [cpp-algorithms]
difficulty: easy
answer_key: "B"
---

## 题目

阅读以下代码，执行后 `v` 的内容是什么？

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    v.erase(
        std::remove_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; }),
        v.end()
    );
    for (int x : v) std::cout << x << " ";
}
```

A. `1 2 3 4 5 6`
B. `1 3 5`
C. `2 4 6`
D. 未定义行为，输出不确定

## 解析

`std::remove_if` 将不满足谓词的元素移到前面，返回新逻辑末尾的迭代器；`v.erase(...)` 删除从该迭代器到 `v.end()` 的元素。最终 `v` 只保留奇数 `1 3 5`。
