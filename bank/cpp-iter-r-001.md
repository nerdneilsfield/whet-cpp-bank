---
qid: cpp-iter-r-001
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "3"
---

## 题目

阅读以下代码，`d` 的值是什么？

```cpp
#include <vector>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40};
    auto it = v.begin();
    auto d = std::distance(it, it + 3);
    std::cout << d << std::endl;
}
```

`d` = ___

## 解析

`std::distance(first, last)` 返回从 `first` 到 `last` 需要推进的步数。`it` 指向 `v[0]`，`it + 3` 指向 `v[3]`，距离为 `3`。对随机访问迭代器（`vector::iterator`）此操作是 O(1)；对双向迭代器（如 `list::iterator`）则是 O(n)。
