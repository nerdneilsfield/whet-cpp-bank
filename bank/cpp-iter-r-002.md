---
qid: cpp-iter-r-002
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "30"
---

## 题目

阅读以下代码，输出是什么？

```cpp
#include <vector>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto it = v.begin();
    std::advance(it, 2);
    std::cout << *it << std::endl;
}
```

输出为：___

## 解析

`std::advance(it, n)` **就地**将迭代器 `it` 向前推进 `n` 步（修改 `it` 自身）。`it` 初始指向 `v[0]`（值 `10`），推进 2 步后指向 `v[2]`（值 `30`），解引用输出 `30`。
