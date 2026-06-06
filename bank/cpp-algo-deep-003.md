---
qid: cpp-algo-deep-003
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: D
---

下列关于 `std::rotate` 的描述哪项**正确**？

```cpp
std::vector<int> v{1, 2, 3, 4, 5};
std::rotate(v.begin(), v.begin() + 2, v.end());
// v 现在是 3 4 5 1 2
```

A. `std::rotate` 与 `std::reverse` 等价，都是把序列反转
B. `std::rotate` 要求容器是双向链表
C. 中间参数指定要保留在头部的元素个数
D. 中间参数 `new_first` 指定旋转后**成为新首元素**的位置，相当于循环左移 `(new_first - first)` 位

## Explanation

正确答案是 D：std::rotate(first, new_first, last) 会让 new_first 指向的元素成为旋转后的首元素。示例中 v.begin()+2 指向 3，因此结果是 3 4 5 1 2，相当于循环左移 2 位。误区是把 rotate 理解成 reverse；reverse 是整体反转，语义完全不同。
