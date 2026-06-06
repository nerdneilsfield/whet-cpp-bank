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

正确答案是 B。`std::remove_if` 不直接删除元素，而是把“不满足删除条件”的元素前移，并返回新逻辑末尾；这里谓词为 `x % 2 == 0`，偶数被判定为要移除。随后 `v.erase(new_end, v.end())` 真正删掉尾部无效区间，所以容器只剩奇数 `1 3 5`。这正是 erase-remove idiom。
