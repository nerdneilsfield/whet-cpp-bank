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

---

**解析：**

`std::rotate(first, new_first, last)` 把 `[first, new_first)` 与 `[new_first, last)` 两段交换位置，使 `new_first` 指向的元素成为新的首元素。等价于循环左移 `n = new_first - first` 位。

返回值（C++11 起）是原 `first` 元素旋转后所在的位置。复杂度 O(last − first)。`std::reverse` 是反转，二者完全不同。`std::rotate` 只要求 ForwardIterator，但提供 RandomAccess 时更高效。
