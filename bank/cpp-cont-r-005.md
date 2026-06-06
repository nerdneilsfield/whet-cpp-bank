---
qid: cpp-cont-r-005
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "B"
---

## 题目

以下代码输出什么？

```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(5);  // 重复插入
    s.insert(1);
    s.insert(3);  // 重复插入
    std::cout << s.size() << std::endl;
    for (int x : s) std::cout << x << " ";
}
```

A. `5` / `5 3 5 1 3`
B. `3` / `1 3 5`
C. `3` / `5 3 1`
D. `2` / `1 5`

## 解析

`std::set` 不允许重复元素，插入已存在的元素会被忽略。插入 `5, 3, 5, 1, 3` 后，实际存储 `{1, 3, 5}`，`size()` 为 `3`。遍历按升序输出 `1 3 5`。若需要允许重复，应使用 `std::multiset`。
