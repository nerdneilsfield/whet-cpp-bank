---
qid: cpp-cont-r-003
type: single
kp: [cpp-containers]
difficulty: easy
answer_key: "A"
---

## 题目

以下代码输出什么？

```cpp
#include <queue>
#include <iostream>

int main() {
    std::priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);
    pq.push(5);
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
}
```

A. `5 4 3 1 1`
B. `1 1 3 4 5`
C. `3 1 4 1 5`（插入顺序）
D. `5 4 3 2 1`

## 解析

`std::priority_queue` 默认是最大堆（`std::less<int>`），每次 `top()` 返回当前最大元素。弹出顺序为 `5 4 3 1 1`（降序）。若要最小堆，需用 `std::priority_queue<int, std::vector<int>, std::greater<int>>`。
