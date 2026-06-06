---
qid: cpp-algo-020
type: multi
kp: [cpp-algorithms]
difficulty: easy
answer_key: [A, C, D]
---

以下代码存在哪些问题？（多选）

```cpp
#include <algorithm>
#include <list>

int main() {
    std::list<int> lst = {5, 3, 1, 4, 2};
    std::sort(lst.begin(), lst.end());          // (1)
    bool found = std::binary_search(lst.begin(), lst.end(), 3);  // (2)
}
```

A. 第 (1) 行：`std::sort` 要求随机访问迭代器，`std::list` 只提供双向迭代器，编译失败
B. 第 (1) 行：`std::sort` 可以用于 `std::list`，没有问题
C. 第 (2) 行：若先用 `std::list::sort()` 排序后再调用 `std::binary_search` 才是正确用法
D. 应改用 `lst.sort()` 对 `std::list` 排序，因为成员函数 `sort` 专为链表设计
